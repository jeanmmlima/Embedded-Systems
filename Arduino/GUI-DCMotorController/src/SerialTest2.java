import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import gnu.io.CommPortIdentifier; 
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import java.io.IOException;
import java.io.InputStream;
import java.util.Enumeration;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import static jdk.nashorn.tools.ShellFunctions.input;

public class SerialTest2  {
	SerialPort serialPort;
        
       
	private static final String PORT_NAMES = "COM1"; 

	private OutputStream output;
	
	private static final int TIME_OUT = 2000;
	
	private static final int DATA_RATE = 9600;
        private BufferedReader input;
        
        public SerialTest2(){
            this.iniciar();
        }

	public void iniciar() {

		CommPortIdentifier portId = null;
		Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();

		while (portEnum.hasMoreElements()) {
			CommPortIdentifier currPortId = (CommPortIdentifier) portEnum.nextElement();
			String portName = PORT_NAMES;
				if (currPortId.getName().equals(portName)) {
					portId = currPortId;
					break;
				}
			
		}
		if (portId == null) {
			System.out.println("Porta Nao foi encontrada");
			return;
		}

		try {
                    serialPort = (SerialPort) portId.open(this.getClass().getName(),TIME_OUT);		
                    serialPort.setSerialPortParams(DATA_RATE, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
                    output = serialPort.getOutputStream();
                    
		} catch (Exception e) {
			System.err.println(e.toString());
		}
	}
        
        public String checarPorta(){
            if(serialPort != null){
                return "CONECTADO";
            }
            return "DESCONECTADO";
        }

	public synchronized void close() {
		if (serialPort != null) {
			serialPort.removeEventListener();
			serialPort.close();
		}
	}
        
        public void escreve(char s){
            try {
                output.write(s);
            } catch (Exception e) {
                System.err.println(e.toString());
            }
        }
        
        public synchronized void serialEvent(SerialPortEvent oEvent) {
		if (oEvent.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
			try {
				String inputLine=input.readLine();
				System.out.println(inputLine);
			} catch (Exception e) {
				System.err.println(e.toString());
			}
		}
		// Ignore all the other eventTypes, but you should consider the other ones.
	}

	
}
