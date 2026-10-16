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
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainActivity extends Activity {
    private static final int PICK_MODEL = 41;
    private static final String MODEL_NAME = "nimo-model.gguf";
    private TextView chat, status;
    private EditText input;
    private Button send, loadButton;
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
        subtitle.setText("Offline AI • model runs locally after setup");
        subtitle.setTextSize(13);
        root.addView(subtitle);

        loadButton = new Button(this);
        loadButton.setText("Choose GGUF model");
        root.addView(loadButton);
        loadButton.setOnClickListener(v -> chooseModel());

        status = new TextView(this);
        status.setText("Download a compatible SmolLM2-135M-Instruct GGUF file, then choose it here.");
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
        if (stored.exists()) {
            modelPath = stored.getAbsolutePath();
            status.setText("A saved model was found. Tap Load saved model.");
            loadButton.setText("Load saved model");
            loadButton.setOnClickListener(v -> loadModel(modelPath));
        }
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
        status.setText("Copying model to app storage. Please wait...");
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
        status.setText("Loading model. This may take time; 1 GB RAM may be insufficient.");
        worker.execute(() -> {
            String result;
            try { result = nativeLoadModel(path); }
            catch (Throwable t) { result = "Load failed: " + t.getMessage(); }
            final String message = result;
            runOnUiThread(() -> {
                status.setText(message);
                loadButton.setEnabled(true);
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
