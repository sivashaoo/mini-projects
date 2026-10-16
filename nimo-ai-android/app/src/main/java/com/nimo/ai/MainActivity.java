package com.nimo.ai;

import android.app.Activity;
import android.os.Bundle;
import android.graphics.Typeface;
import android.view.inputmethod.InputMethodManager;
import android.content.Context;
import android.widget.*;
import android.text.method.ScrollingMovementMethod;

public class MainActivity extends Activity {
    private TextView chat;
    private EditText input;

    @Override public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        LinearLayout root = new LinearLayout(this);
        root.setOrientation(LinearLayout.VERTICAL);
        root.setPadding(18, 18, 18, 18);

        TextView title = new TextView(this);
        title.setText("NIMO AI");
        title.setTextSize(24);
        title.setTypeface(null, Typeface.BOLD);
        root.addView(title);

        TextView subtitle = new TextView(this);
        subtitle.setText("Offline small-language-model app • early development build");
        subtitle.setTextSize(13);
        root.addView(subtitle);

        chat = new TextView(this);
        chat.setText("NIMO AI starter loaded. This build does not yet run an LLM. Native inference and local model loading must be implemented and tested before this becomes an offline chatbot.");
        chat.setTextSize(16);
        chat.setMovementMethod(new ScrollingMovementMethod());
        ScrollView scroll = new ScrollView(this);
        scroll.addView(chat);
        root.addView(scroll, new LinearLayout.LayoutParams(-1, 0, 1f));

        input = new EditText(this);
        input.setHint("Type a message");
        root.addView(input);

        Button send = new Button(this);
        send.setText("Send");
        root.addView(send);
        send.setOnClickListener(v -> {
            String prompt = input.getText().toString().trim();
            if (prompt.isEmpty()) return;
            chat.append("\n\nYou: " + prompt + "\n\nNIMO: The language model is not connected in this starter build yet.");
            input.setText("");
            ((InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE))
                .hideSoftInputFromWindow(input.getWindowToken(), 0);
        });
        setContentView(root);
    }
}
