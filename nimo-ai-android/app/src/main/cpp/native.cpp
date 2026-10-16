#include <jni.h>
#include <string>
#include <vector>
#include <mutex>
#include "llama.h"

namespace {
    llama_model * g_model = nullptr;
    llama_context * g_ctx = nullptr;
    const llama_vocab * g_vocab = nullptr;
    std::mutex g_mutex;
    bool g_backend_ready = false;

    std::string fromJava(JNIEnv * env, jstring value) {
        if (!value) return {};
        const char * chars = env->GetStringUTFChars(value, nullptr);
        if (!chars) return {};
        std::string result(chars);
        env->ReleaseStringUTFChars(value, chars);
        return result;
    }
    void unloadModel() {
        if (g_ctx) { llama_free(g_ctx); g_ctx = nullptr; }
        if (g_model) { llama_model_free(g_model); g_model = nullptr; }
        g_vocab = nullptr;
    }
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_nimo_ai_MainActivity_nativeLoadModel(JNIEnv * env, jobject, jstring jpath) {
    std::lock_guard<std::mutex> lock(g_mutex);
    unloadModel();
    const std::string path = fromJava(env, jpath);
    if (path.empty()) return env->NewStringUTF("Choose a GGUF model file first.");
    if (!g_backend_ready) { llama_backend_init(); g_backend_ready = true; }

    llama_model_params mp = llama_model_default_params();
    mp.n_gpu_layers = 0;
    mp.use_mmap = true;
    g_model = llama_model_load_from_file(path.c_str(), mp);
    if (!g_model) return env->NewStringUTF("Could not load the GGUF file. Check the file and available RAM.");

    llama_context_params cp = llama_context_default_params();
    cp.n_ctx = 640;
    cp.n_batch = 512;
    cp.n_ubatch = 128;
    cp.n_threads = 2;
    cp.n_threads_batch = 2;
    g_ctx = llama_init_from_model(g_model, cp);
    if (!g_ctx) {
        unloadModel();
        return env->NewStringUTF("Could not create inference context. The phone may not have enough free RAM.");
    }
    g_vocab = llama_model_get_vocab(g_model);
    return env->NewStringUTF("Model loaded. Responses are generated locally.");
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_nimo_ai_MainActivity_nativeGenerate(JNIEnv * env, jobject, jstring jprompt) {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (!g_model || !g_ctx || !g_vocab) return env->NewStringUTF("Load a GGUF model first.");
    const std::string userText = fromJava(env, jprompt);
    if (userText.empty()) return env->NewStringUTF("Please enter a message.");

    const std::string prompt = "<|im_start|>user\n" + userText +
        "<|im_end|>\n<|im_start|>assistant\n";
    int32_t needed = -llama_tokenize(g_vocab, prompt.c_str(),
        static_cast<int32_t>(prompt.size()), nullptr, 0, true, true);
    if (needed <= 0) return env->NewStringUTF("Could not tokenize the prompt.");
    if (needed > 440) return env->NewStringUTF("Message is too long for this low-memory configuration. Please shorten it.");

    std::vector<llama_token> tokens(static_cast<size_t>(needed));
    int32_t n_prompt = llama_tokenize(g_vocab, prompt.c_str(),
        static_cast<int32_t>(prompt.size()), tokens.data(), needed, true, true);
    if (n_prompt < 0) return env->NewStringUTF("Prompt tokenization failed.");

    llama_kv_cache_clear(g_ctx);
    llama_batch batch = llama_batch_get_one(tokens.data(), n_prompt);
    if (llama_decode(g_ctx, batch) != 0)
        return env->NewStringUTF("Prompt evaluation failed. Try a shorter message or restart NIMO.");

    llama_sampler_chain_params sp = llama_sampler_chain_default_params();
    llama_sampler * sampler = llama_sampler_chain_init(sp);
    llama_sampler_chain_add(sampler, llama_sampler_init_temp(0.7f));
    llama_sampler_chain_add(sampler, llama_sampler_init_dist(1234));
    std::string answer;
    for (int i = 0; i < 128; ++i) {
        llama_token token = llama_sampler_sample(sampler, g_ctx, -1);
        llama_sampler_accept(sampler, token);
        if (llama_vocab_is_eog(g_vocab, token)) break;
        char piece[256];
        int n = llama_token_to_piece(g_vocab, token, piece, sizeof(piece), 0, true);
        if (n > 0) answer.append(piece, static_cast<size_t>(n));
        batch = llama_batch_get_one(&token, 1);
        if (llama_decode(g_ctx, batch) != 0) break;
    }
    llama_sampler_free(sampler);
    if (answer.empty()) answer = "(No text generated. Try a compatible instruct GGUF model.)";
    return env->NewStringUTF(answer.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_nimo_ai_MainActivity_nativeUnloadModel(JNIEnv *, jobject) {
    std::lock_guard<std::mutex> lock(g_mutex);
    unloadModel();
}
