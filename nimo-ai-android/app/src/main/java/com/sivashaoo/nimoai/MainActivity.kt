package com.sivashaoo.nimoai

import android.app.Activity
import android.os.Bundle
import android.graphics.Typeface
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.LinearLayout
import android.widget.ScrollView
import android.widget.TextView

class MainActivity : Activity() {
    private lateinit var transcript: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val root = LinearLayout(this).apply {
            orientation = LinearLayout.VERTICAL
            setPadding(20, 24, 20, 16)
        }
        val title = TextView(this).apply {
            text = "NIMO AI"
            textSize = 28f
            setTypeface(null, Typeface.BOLD)
        }
        root.addView(title)
        root.addView(TextView(this).apply {
            text = "Personal on-device AI • Prototype"
            textSize = 14f
        })
        val scroll = ScrollView(this)
        transcript = TextView(this).apply {
            textSize = 16f
            text = "\nWelcome. This is the app shell. The offline language-model runtime is not integrated yet."
            setPadding(0, 18, 0, 18)
        }
        scroll.addView(transcript)
        root.addView(scroll, LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, 0, 1f))
        val input = EditText(this).apply { hint = "Type a message"; minLines = 1; maxLines = 4 }
        root.addView(input)
        root.addView(Button(this).apply {
            text = "Send"
            setOnClickListener {
                val prompt = input.text.toString().trim()
                if (prompt.isNotEmpty()) {
                    transcript.append("\n\nYou: $prompt\nNIMO AI: The language model has not been connected yet. This prototype does not generate AI responses.")
                    input.text.clear()
                }
            }
        })
        setContentView(root)
    }
}
