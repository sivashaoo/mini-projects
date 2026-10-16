# NIMO AI — Android offline LLM starter

This folder contains a starter Android app intended to run a small local GGUF language model.

## Honest status
This is a **starter scaffold, not a completed or verified APK**. The Android UI and cloud build workflow are provided, but the native llama.cpp inference bridge and model-file selection still need to be completed and tested. Do not install or describe it as a working AI chatbot yet.

## Target
- Android app: NIMO AI
- Suggested model: SmolLM2-135M-Instruct, 4-bit GGUF
- Offline generation after the model is downloaded
- Target devices: low-memory Android phones; 1 GB RAM support is not guaranteed and must be tested

## Build on a phone using GitHub Actions
The workflow in `.github/workflows/nimo-ai-android.yml` can build a debug APK from this repository. Open **Actions → Build NIMO AI Android APK**, run the workflow, then download the artifact if the build succeeds.

## Model
Choose a compatible GGUF file from the official model repository:
https://huggingface.co/unsloth/SmolLM2-135M-Instruct-GGUF

Model weights are not included in this repository or APK. This project does not train a new model; it is intended to run an existing pretrained model.

## Next implementation tasks
1. Complete and validate JNI inference against a pinned llama.cpp version.
2. Implement Android Storage Access Framework model selection and permission-safe file access.
3. Add generation on a background thread, cancellation, and memory-conscious context settings.
4. Test on the target phone before claiming 1 GB RAM compatibility.
