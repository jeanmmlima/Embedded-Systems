
import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author jeanmarioml
 */
public class SerialLeds extends javax.swing.JFrame {

SerialTest2 serial;
    /**
     * Creates new form SerialLeds
     */
    public SerialLeds() {
         serial = new SerialTest2();
        initComponents();
        statusSerial.setText(serial.checarPorta());

    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        fechaConexaoSerial = new javax.swing.JButton();
        statusSerial = new javax.swing.JLabel();
        labelAngulo = new javax.swing.JLabel();
        textAngulo = new javax.swing.JTextField();
        btnSetAngulo = new javax.swing.JButton();
        jLabel4 = new javax.swing.JLabel();
        labelAnguloAtual = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                formWindowClosing(evt);
            }
        });

        fechaConexaoSerial.setText("Fechar");
        fechaConexaoSerial.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                fechaConexaoSerialActionPerformed(evt);
            }
        });

        statusSerial.setText("jLabel4");

        labelAngulo.setText("Angulo: ");

        btnSetAngulo.setText("Enviar");
        btnSetAngulo.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnSetAnguloActionPerformed(evt);
            }
        });

        jLabel4.setText("Digitar valor entre -90 e 90");

        labelAnguloAtual.setText("Angulo Atual: ");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(80, 80, 80)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(labelAnguloAtual)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(labelAngulo)
                        .addGap(18, 18, 18)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(btnSetAngulo, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(textAngulo, javax.swing.GroupLayout.PREFERRED_SIZE, 147, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(jLabel4)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 177, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(statusSerial)
                    .addComponent(fechaConexaoSerial))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(36, 36, 36)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(labelAngulo)
                            .addComponent(textAngulo, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jLabel4))
                        .addGap(18, 18, 18)
                        .addComponent(btnSetAngulo)
                        .addGap(34, 34, 34)
                        .addComponent(labelAnguloAtual))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(statusSerial)
                        .addGap(4, 4, 4)
                        .addComponent(fechaConexaoSerial)))
                .addContainerGap(364, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void formWindowClosing(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosing
        // TODO add your handling code here:
        serial.close();
    }//GEN-LAST:event_formWindowClosing

    private void btnSetAnguloActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnSetAnguloActionPerformed
        // TODO add your handling code here:
        serial.escreve('0');
        String angulo = textAngulo.getText();
        for(int i = 0; i < angulo.length(); i++){
            serial.escreve(angulo.charAt(i));
        }
    }//GEN-LAST:event_btnSetAnguloActionPerformed

    private void fechaConexaoSerialActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_fechaConexaoSerialActionPerformed
        // TODO add your handling code here:
        serial.close();
    }//GEN-LAST:event_fechaConexaoSerialActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(SerialLeds.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(SerialLeds.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(SerialLeds.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(SerialLeds.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            
            public void run() {
                new SerialLeds().setVisible(true);
            }
        });
        
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnSetAngulo;
    private javax.swing.JButton fechaConexaoSerial;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel labelAngulo;
    private javax.swing.JLabel labelAnguloAtual;
    private javax.swing.JLabel statusSerial;
    private javax.swing.JTextField textAngulo;
    // End of variables declaration//GEN-END:variables
}
