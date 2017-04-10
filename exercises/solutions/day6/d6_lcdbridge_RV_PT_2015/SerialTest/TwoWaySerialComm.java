/**
 * Authors: Rick Vogel, Philipp Thomasberger
 * Created: 24.09.2015
 */

package serialTest;

import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;



import java.io.FileDescriptor;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class TwoWaySerialComm
{
    public TwoWaySerialComm()
    {
        super();
    }
    
    void connect ( String portName ) throws Exception
    {
        CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
        if ( portIdentifier.isCurrentlyOwned() )
        {
            System.out.println("Error: Port is currently in use");
        }
        else
        {
            CommPort commPort = portIdentifier.open(this.getClass().getName(),2000);
            
            if ( commPort instanceof SerialPort )
            {
                SerialPort serialPort = (SerialPort) commPort;
                // Specify baud, etc. in this case it's 115200 8N1
                serialPort.setSerialPortParams(115200,SerialPort.DATABITS_8,SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);
                
                OutputStream out = serialPort.getOutputStream();           
                (new Thread(new SerialWriter(out))).start();
                commPort.close();
            }
            else
            {
                System.out.println("Error: Only serial ports are handled by this example.");
            }
        }     
    }
    
    /** */
    public static class SerialWriter implements Runnable 
    {
        OutputStream out;
        
        public SerialWriter ( OutputStream out )
        {
            this.out = out;
        }
        
        public void run ()
        {
        	int dir=0;
        	int test=0;

        	while(true) {
        		try {
					//System.in.read();
        			byte out[] = new byte[1025];
        			out[0] = (byte)0xBB;
        			for(int i=1;i<1025;i++) {
        				out[i] = (byte)(1<<test);
        			}
        			if(dir == 0) {
	        			if (test < 7)
	        				test++;
	        			else
	        				test=0;
	        		}
        			else {
        				if(test > 0)
        					test--;
        				else
        					dir=0;
        			}
        				
        			this.out.write(out);
	        		Thread.sleep(30);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} 
        	}
        }
    }
    
    public static void main ( String[] args )
    {
        try
        {
        	// Specify COM-Port
            (new TwoWaySerialComm()).connect("COM5");
        }
        catch ( Exception e )
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
