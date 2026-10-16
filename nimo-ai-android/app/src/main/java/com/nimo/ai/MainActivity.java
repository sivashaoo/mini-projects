package com.nimo.ai;

import android.app.Activity;
import android.os.Bundle;
import android.graphics.Typeface;
import android.content.Intent;
import android.net.Uri;
import android.view.inputmethod.InputMethodManager;
import android.content.Context;
import android.widget.*;
import android.text.method.ScrollingMovementMethod;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainActivity extends Activity {
    private static final int PICK_MODEL = 41;
    private static final String MODEL_NAME = "SmolLM2-135M-Instruct-Q4_K_M.gguf";
    private static final String MODEL_URL =
        "https://huggingface.co/unsloth/SmolLM2-135M-Instruct-GGUF/resolve/main/SmolLM2-135M-Instruct-Q4_K_M.gguf?download=true";
    private TextView chat, status;
    private EditText input;
    private Button send, loadButton, downloadButton;
    private final ExecutorService worker = Executors.newSingleThreadExecutor();
    private String modelPath = "";
    private boolean busy = false;

    static { System.loadLibrary("nimo_native"); }
    private native String nativeLoadModel(String path);
    private native String nativeGenerate(String prompt);
    private native void nativeUnloadModel();

    @Override public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        LinearLayout root = new LinearLayout(this);
        root.setOrientation(LinearLayout.VERTICAL);
        root.setPadding(16, 16, 16, 16);

        TextView title = new TextView(this);
        title.setText("NIMO AI");
        title.setTextSize(25);
        title.setTypeface(null, Typeface.BOLD);
        root.addView(title);

        TextView subtitle = new TextView(this);
        subtitle.setText("Offline AI • download the model once, then chat without internet");
        subtitle.setTextSize(13);
        root.addView(subtitle);

        downloadButton = new Button(this);
        downloadButton.setText("Download model (~105 MB)");
        root.addView(downloadButton);
        downloadButton.setOnClickListener(v -> downloadModel());

        loadButton = new Button(this);
        loadButton.setText("Choose existing GGUF model");
        root.addView(loadButton);
        loadButton.setOnClickListener(v -> chooseModel());

        status = new TextView(this);
        status.setText("Download the recommended SmolLM2-135M-Instruct Q4_K_M model. Keep at least 300 MB free.");
        status.setTextSize(13);
        root.addView(status);

        chat = new TextView(this);
        chat.setText("NIMO: Load a model to start chatting offline.");
        chat.setTextSize(16);
        chat.setPadding(4, 12, 4, 12);
        chat.setMovementMethod(new ScrollingMovementMethod());
        ScrollView scroll = new ScrollView(this);
        scroll.addView(chat);
        root.addView(scroll, new LinearLayout.LayoutParams(-1, 0, 1f));

        input = new EditText(this);
        input.setHint("Ask something...");
        root.addView(input);

        send = new Button(this);
        send.setText("Send");
        root.addView(send);
        send.setOnClickListener(v -> sendPrompt());
        setContentView(root);

        File stored = new File(getFilesDir(), MODEL_NAME);
        if (stored.exists() && stored.length() > 1000000) {
            modelPath = stored.getAbsolutePath();
            status.setText("Saved model found. Tap Load saved model.");
            loadButton.setText("Load saved model");
            loadButton.setOnClickListener(v -> loadModel(modelPath));
        }
    }

    private void downloadModel() {
        if (busy) return;
        busy = true;
        downloadButton.setEnabled(false);
        loadButton.setEnabled(false);
        status.setText("Downloading approximately 105 MB. Keep the app open and use Wi-Fi if possible.");
        worker.execute(() -> {
            File target = new File(getFilesDir(), MODEL_NAME);
            File partial = new File(getFilesDir(), MODEL_NAME + ".part");
            HttpURLConnection connection = null;
            try {
                connection = (HttpURLConnection) new URL(MODEL_URL).openConnection();
                connection.setConnectTimeout(20000);
                connection.setReadTimeout(60000);
                connection.setInstanceFollowRedirects(true);
                connection.setRequestProperty("User-Agent", "NIMO-AI-Android/0.2");
                connection.connect();
                int code = connection.getResponseCode();
                if (code != 200) throw new Exception("Download server returned HTTP " + code);
                long total = connection.getContentLengthLong();
                try (InputStream in = connection.getInputStream();
                     FileOutputStream out = new FileOutputStream(partial)) {
                    byte[] buffer = new byte[128 * 1024];
                    long copied = 0;
                    int count;
                    while ((count = in.read(buffer)) != -1) {
                        out.write(buffer, 0, count);
                        copied += count;
                        if (total > 0) {
                            final int percent = (int)(copied * 100 / total);
                            runOnUiThread(() -> status.setText("Downloading model: " + percent + "%"));
                        } else {
                            final long mb = copied / (1024 * 1024);
                            runOnUiThread(() -> status.setText("Downloaded " + mb + " MB..."));
                        }
                    }
                }
                if (partial.length() < 50000000) throw new Exception("Downloaded file is unexpectedly small; check your connection and retry.");
                if (target.exists()) target.delete();
                if (!partial.renameTo(target)) throw new Exception("Could not save the downloaded model.");
                runOnUiThread(() -> {
                    modelPath = target.getAbsolutePath();
                    status.setText("Download complete. Loading model...");
                    busy = false;
                    downloadButton.setEnabled(true);
                    loadButton.setEnabled(true);
                    loadModel(modelPath);
                });
            } catch (Exception e) {
                partial.delete();
                final String message = "Download failed: " + e.getMessage();
                runOnUiThread(() -> {
                    status.setText(message);
                    busy = false;
                    downloadButton.setEnabled(true);
                    loadButton.setEnabled(true);
                });
            } finally {
                if (connection != null) connection.disconnect();
            }
        });
    }

    private void chooseModel() {
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("*/*");
        startActivityForResult(intent, PICK_MODEL);
    }

    @Override protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode != PICK_MODEL || resultCode != RESULT_OK || data == null || data.getData() == null) return;
        Uri uri = data.getData();
        status.setText("Copying model into app storage. Please wait...");
        loadButton.setEnabled(false);
        worker.execute(() -> {
            try {
                File target = new File(getFilesDir(), MODEL_NAME);
                try (InputStream in = getContentResolver().openInputStream(uri);
                     FileOutputStream out = new FileOutputStream(target)) {
                    if (in == null) throw new Exception("Could not open selected file.");
                    byte[] buffer = new byte[256 * 1024];
                    int count;
                    while ((count = in.read(buffer)) != -1) out.write(buffer, 0, count);
                }
                runOnUiThread(() -> {
                    modelPath = target.getAbsolutePath();
                    status.setText("Model copied. Loading...");
                    loadButton.setEnabled(true);
                    loadModel(modelPath);
                });
            } catch (Exception e) {
                runOnUiThread(() -> {
                    status.setText("Model copy failed: " + e.getMessage());
                    loadButton.setEnabled(true);
                });
            }
        });
    }

    private void loadModel(String path) {
        if (busy) return;
        busy = true;
        loadButton.setEnabled(false);
        downloadButton.setEnabled(false);
        status.setText("Loading model. This may take time; 1 GB RAM may be insufficient.");
        worker.execute(() -> {
            String result;
            try { result = nativeLoadModel(path); }
            catch (Throwable t) { result = "Load failed: " + t.getMessage(); }
            final String message = result;
            runOnUiThread(() -> {
                status.setText(message);
                loadButton.setEnabled(true);
                downloadButton.setEnabled(true);
                loadButton.setText("Choose another GGUF model");
                loadButton.setOnClickListener(v -> chooseModel());
                busy = false;
            });
        });
    }

    private void sendPrompt() {
        String prompt = input.getText().toString().trim();
        if (prompt.isEmpty() || busy) return;
        input.setText("");
        ((InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE))
            .hideSoftInputFromWindow(input.getWindowToken(), 0);
        chat.append("\n\nYou: " + prompt + "\n\nNIMO: ");
        busy = true;
        send.setEnabled(false);
        worker.execute(() -> {
            String answer;
            try { answer = nativeGenerate(prompt); }
            catch (Throwable t) { answer = "Generation failed: " + t.getMessage(); }
            final String result = answer;
            runOnUiThread(() -> {
                chat.append(result);
                send.setEnabled(true);
                busy = false;
            });
        });
    }

    @Override protected void onDestroy() {
        worker.execute(() -> { try { nativeUnloadModel(); } catch (Throwable ignored) {} });
        worker.shutdown();
        super.onDestroy();
    }
}
