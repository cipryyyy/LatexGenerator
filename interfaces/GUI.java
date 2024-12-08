package interfaces;

import javax.swing.*;
import javax.swing.text.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

class GUI {
    public static void main(String[] args) {
        JFrame jframe = new JFrame("GUI");
        jframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jframe.setSize(700, 450);
        jframe.setLayout(new BorderLayout());

        double aspectRatio = 700.0 / 450.0;

        JPanel panel = new JPanel(new GridLayout(6, 5, 5, 5));

        String[] headers = {"Esercizio", "Set", "Reps", "Rest", "Note"};
        for (String header : headers) {
            JLabel label = new JLabel(header, SwingConstants.CENTER);
            label.setFont(new Font("Arial", Font.BOLD, 12));
            panel.add(label);
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                JTextField textField = new JTextField();
                if (j == 1 || j == 2) {
                    ((AbstractDocument) textField.getDocument()).setDocumentFilter(new NumericAndSpecialCharFilter());
                }
                textField.setHorizontalAlignment(SwingConstants.CENTER);
                panel.add(textField);
            }
        }

        jframe.add(panel, BorderLayout.CENTER);
        jframe.setResizable(true);

        jframe.addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                int newWidth = jframe.getWidth();
                int newHeight = (int) (newWidth / aspectRatio);

                if (newHeight > jframe.getHeight()) {
                    newHeight = jframe.getHeight();
                    newWidth = (int) (newHeight * aspectRatio);
                }

                jframe.setSize(newWidth, newHeight);
            }
        });

        jframe.setVisible(true);
    }
}

class NumericAndSpecialCharFilter extends DocumentFilter {
    @Override
    public void insertString(FilterBypass fb, int offset, String string, AttributeSet attr) throws BadLocationException {
        if (isValid(string)) {
            super.insertString(fb, offset, string, attr);
        }
    }

    @Override
    public void replace(FilterBypass fb, int offset, int length, String string, AttributeSet attr) throws BadLocationException {
        if (isValid(string)) {
            super.replace(fb, offset, length, string, attr);
        }
    }

    @Override
    public void remove(FilterBypass fb, int offset, int length) throws BadLocationException {
        super.remove(fb, offset, length);
    }

    private boolean isValid(String string) {
        return string.matches("[\\d/\\-]*");
    }
}
