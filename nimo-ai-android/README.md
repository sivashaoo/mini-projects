# NIMO AI — Android Offline LLM

An Android app project for experimenting with a compact, on-device language model.

## Target
- Android APK (debug build)
- Target model size: approximately 120M parameters
- Offline inference after the model file is installed
- Low-memory device target: 1 GB RAM (must be validated on real hardware)

## Important status
This repository currently contains the initial Android project scaffold. It is **not yet a working LLM**: an inference runtime and a compatible quantized model must be integrated before the app can generate model responses. A successful APK compilation alone does not prove offline AI inference works.

## Build
Pushes to main that change this directory trigger the Android build workflow. Download the debug APK from the workflow run's Artifacts section after a successful run.

## Model requirements
Use a small, permissively licensed GGUF model and a compatible Android inference runtime. Model weights should not be committed to Git; they are large binary files and may have separate license terms.

## Planned milestones
1. Build and verify the Android shell.
2. Integrate a mobile inference runtime.
3. Add a quantized ~120M model and model-file selection/download.
4. Test offline generation, memory use, and performance on a 1 GB RAM device.
