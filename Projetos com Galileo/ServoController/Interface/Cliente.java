import java.io.*;
import java.net.*;

public class Cliente {
    public static void main(String[] args) throws IOException {
/* if (args.length != 2) {
            System.err.println(
                "Usage: java EchoClient <host name> <port number>");
            System.exit(1);
        }*/

        String hostName = "josiele.local";
        int portNumber = 7081;
        Socket firstSocket = new Socket(hostName, portNumber);
        PrintWriter out = new PrintWriter(firstSocket.getOutputStream(), true);
        BufferedReader in = new BufferedReader(new InputStreamReader(firstSocket.getInputStream()));
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        String userInput;
        while ((userInput = stdIn.readLine()) != null) 
        {
            out.println(userInput);
            System.out.println("received: " + in.readLine());
        }
        in.close();
        stdIn.close();
        firstSocket.close();

    }
}
