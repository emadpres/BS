package com.simin.simin;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InterfaceAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Deque;
import java.util.Random;

import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.TextView;

public class MainActivity extends Activity {
	
	Button startBt = null ;
	RadioButton server_r = null , client_r = null;
	EditText packetsize_st = null;
	CheckBox error_ch = null;
	EditText filename_st = null;
	TextView LogView = null ;
	DatagramSocket sendsocket = null , receivesocket = null;
	String output="";  // --> Whatever is here will be displayed in Log Windows
	
	// 5 Threads
    Thread myServerThread = null;		//Main
    Thread myServerListenerThread = null;
	Thread myClientThread = null;		//Main
    Thread myClientSenderThread = null;
    Thread alarmerThread = null;

	// Both side Variables
	String fileName = null;
	int numberOfPackets = -1 ;
	int numberOfRemainingPackets = -1;
	boolean[] packetsStatus = null;
	int AlarmMessageLength=5000;		// max length of the List
	int packetSizeByte = -1 ;			// packets Size
	byte[][] fileData = null ;			// Data which is sending/receiving
	boolean errorPosibility;			// if true, 50% error
	Random r = null;					// make random number
	
	//server
	int nextSeq = -1 ;
	boolean TNP_Ack=false;
	int send_interval=50;		// every 50ms one packet is sending to avoid overload

	//client
	boolean requestDelivered = false;
	boolean dataReceivingStarted=false;
	int sendNotdeliverdTimerTime=200;// Timeout time to send list of packets that doesn;t received yet
	boolean timeToSendList=false;	
	boolean allDone=false;			// true when all packets are received
	
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {	// When Program go up
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        startBt = (Button) findViewById(R.id.second_start_button);
        server_r = (RadioButton) findViewById(R.id.second_radio_server);
        client_r = (RadioButton) findViewById(R.id.second_radio_client);
		packetsize_st = (EditText) findViewById(R.id.packet_SIZE_TEXT);
		error_ch = (CheckBox) findViewById(R.id.second_error_check);
        filename_st = (EditText) findViewById(R.id.second_File_Name);
        LogView = (TextView) findViewById(R.id.second_log);

        r = new Random();
		LogTimerHandler.postDelayed(LogTimer, 500); // make LogTimer be called every 500ms to refresh LOG
	        
        startBt.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				
				
				if(v.getId() ==  R.id.second_play_button )	// if Play Button is clicked
				{
					if(allDone)
					{
						Intent intent = new Intent();
						intent.setAction(android.content.Intent.ACTION_VIEW);
						File myFile=new File(Environment.getExternalStorageDirectory().getPath()+"/_"+fileName); 
						intent.setDataAndType(Uri.fromFile(myFile), "audio/*");
						startActivity(intent);
						
					}
					else
					 output += "Can't Play until getting file.\n";
					return;
				}
				
				// Go here, If `Start` Button is clicked
				packetSizeByte = Integer.parseInt(packetsize_st.getText().toString());
				//get packetsize from UI
				if(error_ch.isChecked())
					errorPosibility = true; // get packetsize from UI

				output += ("Packet Size:"+packetSizeByte+" bytes\n");
				 
				
				if ( server_r.isChecked() == true){ // Server START
					
					try {
						sendsocket = new DatagramSocket(2000);
						receivesocket = new DatagramSocket(3000);
						
					} catch (SocketException e) {
						Log.e("ss", "cant create Socket" + e.getMessage());
					}
					
					TNP_Ack=false; // Both below thread use this to proceed
					
					myServerThread	= new Thread( new Runnable() {
						@Override public void run() { 
								try {
									serverFunction();
								} catch (IOException e) {
									Log.e("ss","Some thing Wrong in ServerFunction");
								} 
							}
					});
					myServerThread.start();
					
					myServerListenerThread	= new Thread( new Runnable() {
						@Override public void run() { serverListenerFunction(); }
					});
					//myServerListenerThread.start(); //Start After First Requst
					
					
					
				}
					else { // Client START
					
					 try {
						sendsocket = new DatagramSocket(3000);
						receivesocket = new DatagramSocket(2000);
						
					} catch (SocketException e) {
						Log.e("ss", "cant create Socket" + e.getMessage());
					}
					
					requestDelivered=false; // Both below thread use this to proceed
					
					myClientThread	= new Thread( new Runnable() {
						@Override public void run() {  
								try {
									clientFunction();
								} catch (IOException e) {
									Log.e("ss","Some thing Wrong in ClientFunction");
								} 
							} 
					});
					myClientThread.start();
					
					myClientSenderThread	= new Thread( new Runnable() {
						@Override public void run() {
							clientSenderFunction(); 
							} 
					});
					
					//myClientSenderThread.start();
					
					
				}
				
			}
		});
        
    }
    
    private Handler LogTimerHandler=new Handler();
    
    private Runnable LogTimer=new Runnable() {
   		
   		@Override
   		public void run() {
   			LogView.setText( output ) ;
   			LogTimerHandler.postDelayed(LogTimer, 500L);
   		}
   	};
    
    public void serverFunction () throws IOException
    {
	   FileInputStream fis = null ;
	   DatagramPacket myPacket = null;
	   byte[] buffer = null;
	   
	   
	   boolean haveSthToSend = false ;
	   while(!haveSthToSend)
	   {
		   // Listening for request
		   buffer = new byte[100];
		   myPacket = new DatagramPacket(buffer, buffer.length);
		   
		   Log.i("ss","i'm Listening for client request");
		   output += "Waiting for request...\n";
		   try {
			   receivesocket.receive(myPacket)	;		////////////////////////////////////////
		   } catch (IOException e) {
			   Log.e("ss", "error in listening" + e.getMessage());
		   }
		   fileName = new String(myPacket.getData()) ;
		   fileName = fileName.substring(0,myPacket.getLength()) ;
		   Log.i("ss","requested file: "+ fileName);
		   //if file exist
		   boolean fileExist=true;
		   try {
			   fis = new FileInputStream("/mnt/sdcard/"+fileName);
		   } catch (FileNotFoundException e) {
			   e.printStackTrace();
			   fileExist=false;
		   }
		   if(fileExist)
			   haveSthToSend=true;
		   else
			   Log.i("ss","File Doesn't exist");
	   
	   } //end of While!HaveSthToSend)
	   /*********************************************************************************/
		// Analysing File
	   Log.i("ss","Handling Reuest for file:"+fileName);
		File requestedFile=new File("/mnt/sdcard/"+fileName);
		try {
			fis = new FileInputStream(requestedFile);
			} catch (FileNotFoundException e) {
				e.printStackTrace();
				Log.e("ss","File Doesn't exist");
			}
		numberOfPackets = 0 ;
		numberOfPackets = (int) ( requestedFile.length()/ (packetSizeByte-6) );
		if ( requestedFile.length() % (packetSizeByte-6)!= 0 )
			numberOfPackets++ ;
		Log.i("ss","Total Number of Packets(TNP): "+numberOfPackets) ;
		output += ("Requsted File: /mnt/sdcard/"+fileName+"\n");
		output += ("Total Number of Packets(TNP): "+numberOfPackets+"\n");
		// creating a package carry total packets number
		byte[] sizeOfFile = new byte[9];
		sizeOfFile = ("TNP"+Integer.toString(numberOfPackets)).getBytes() ;
		Log.i("ss","SizeOfFileString to Send as delivery to client:"+new String(sizeOfFile));
		TNP_Ack = false;
		myServerListenerThread.start(); // start ServertListener	//////////////////////////////
		
		Log.i("ss","Sending TNP to client"+numberOfPackets);
		while(TNP_Ack==false)
		{
			try {
				myPacket = new DatagramPacket(sizeOfFile, sizeOfFile.length, //length is 9 OR LESS !!
						InetAddress.getByName("10.0.2.2"),2000);
				sendsocket.send(myPacket);	///////////////////////////////////////////////////////
				Log.i("ss","TNPSent");
			}catch (IOException e) {
				Log.e("ss", "error in Sending First packet to client" + e.getMessage());
			}
				
			try { // wait 100ms and loop again | Send until, Its ack recieved by ServertListener
				Thread.sleep(4000);
			} catch (InterruptedException e) {
				e.printStackTrace();
				Log.e("ss", "send thread sucked");
			}
		}
	   	Log.e("ss","Server:TNP Acked");
    	Log.i("ss","Server Hoooora. I WILL send File packets");
		
	/*********************************************************************************/
		//Preparing File to send
		Log.i("ss","Preparing File to send");
		output += "Data Creating!\n";
		
		fileData = new byte[numberOfPackets][] ;
		
		byte[] currentPacketNumber= new byte[6];
		for ( int i=1 ; i<= numberOfPackets-1 ; i++ )
		{
			int n=0;
			try {
				Log.i("ss","Preparing Packet"+i+"OF"+numberOfPackets);
				fileData[i-1] = new byte[packetSizeByte];
				//Log.i("ss","1 fileData[i-1]:"+new String(fileData[i-1]));
				fis.read(fileData[i-1],6, packetSizeByte-6);
				currentPacketNumber = Integer.toString(i-1).getBytes(); //packet number 0->numberOfPackets-1(here up to numberOfPackets-2)
				for(n=1;n<=6-currentPacketNumber.length;n++)fileData[i-1][n-1]='0'; //put 0 to fill 6 byte
				for(;n<=6;n++) fileData[i-1][n-1]=currentPacketNumber[n-(6-currentPacketNumber.length)-1];
				Log.i("ss","_DATA#"+i+"is:"+(new String(fileData[i-1])).substring(0, 15));
				//Log.i("ss","3fileData[i-1]:"+new String(fileData[i-1]));
			}catch (IOException e) {
				Log.e("ss","Reading File Error "+ e.getMessage() );
			}
		}// end of FOR
		
		Log.i("ss","Preparing LAST Packet #"+numberOfPackets);
		try {
			int n;
			Log.e("ss","Packet Size:"+(requestedFile.length()-(numberOfPackets-1)*(packetSizeByte-6)+6));
			fileData[numberOfPackets-1] = new byte[(int) (requestedFile.length()-(numberOfPackets-1)*(packetSizeByte-6)+6)];
			fis.read(fileData[numberOfPackets-1],6,(int) (requestedFile.length()-(numberOfPackets-1)*(packetSizeByte-6)));
			Log.i("ss","_DATA#"+numberOfPackets+"is:"+(new String(fileData[numberOfPackets-1])).substring(0, 15));
			currentPacketNumber = Integer.toString(numberOfPackets-1).getBytes();
			for(n=1;n<=6-currentPacketNumber.length;n++)fileData[numberOfPackets-1][n-1]='0'; //put 0 to fill 6 byte
			for(;n<=6;n++) fileData[numberOfPackets-1][n-1]=currentPacketNumber[n-(6-currentPacketNumber.length)-1];
			//Log.i("ss","LastPacket Content"+new String(fileData[numberOfPackets-1]));
			Log.i("ss","+DATA#"+numberOfPackets+"is:"+(new String(fileData[numberOfPackets-1])).substring(0, 15));
		}catch (IOException e) {
			Log.e("ss","Reading File Error "+ e.getMessage() );
		}
		
		Log.i("ss","File Data Prepared!");
		output += "Data Done!\n\n ******* Start *******";
/*********************************************************************************/
	   numberOfRemainingPackets = numberOfPackets ;
	   packetsStatus = new boolean[numberOfPackets];
	   buffer = new byte[AlarmMessageLength];
	   for(int i=0; i<numberOfPackets; i++)
		   packetsStatus[i]=false; // assume all packet shoudl send
	   
	   while(numberOfRemainingPackets>0)
	   {
		   // In this loop
		   // 1. send unacked packages
		   // 2. wait for list of not-delivered and update packetsStatus
		   
		   //1
		   output += (">> Remained:"+numberOfRemainingPackets+" <<\n");
		   for(int i=0;i<numberOfPackets;i++)
		   {
			   if(packetsStatus[i]==true)
				   continue;
			   
			   Log.i("ss" , "Sending packet "+i );
			   
			   output+=("Sending #"+i+"\n"); 
			   
			   try {
				   myPacket = new DatagramPacket( fileData[i], fileData[i].length,  
														InetAddress.getByName("10.0.2.2"), 2000 );
				   Log.i("ss","FileData Size:"+fileData[i].length);
				   Log.i("ss","FileData:"+(new String(fileData[i])).substring(0, 12));
				   //Log.i("ss" , "packet#"+i+": "+(new String(myPacket.getData())).substring(0,15) );
					sendsocket.send(myPacket);
				}catch (Exception e) {
					Log.e("ss", "Cant Send Data #"+ i + e.getMessage());
					numberOfRemainingPackets=0; //Tmp
				}
			
			   try {
					Thread.sleep(send_interval);
				} catch (InterruptedException e) {
					e.printStackTrace();
					Log.e("ss", "send thread sucked");
				}
		   }	   
		   //2
		   output+=("*****************\n"); 
		   for(int i=0; i<numberOfPackets; i++)
			   packetsStatus[i]=true; // assume all packet has delivered After above send cycle
		   numberOfRemainingPackets=0;
		   myPacket = new DatagramPacket(buffer, buffer.length);
		   Log.i("ss","Wait for ****");
		   
		   receivesocket.receive(myPacket);
		   
		   Log.i("ss","Maybe Got ***");
		   String info = (new String(myPacket.getData())).substring(0,myPacket.getLength());
		   if(info.startsWith("DONE"))
			   numberOfRemainingPackets=0;
		   else
		   {
			   Log.e("ss","Analysing Undeliver list from client");
			   int first=0,second= info.indexOf('*',0);
			   String tmp="";
			   while(second!=-1)
			   {
				   numberOfRemainingPackets++;
				   tmp = info.substring(first,second);
				   packetsStatus[Integer.parseInt(tmp)]=false;
				   Log.i("ss","List Item:"+tmp);
				   first=second+1;
				   second= info.indexOf('*',first);
			   }
		   }
		   // Let's Send If Sth Remained   
	   }
	   
	   output += "\n**Send Done successfully**\n";

   }
      
    public void serverListenerFunction()	// Listen for TNP ACK
    {
    	DatagramPacket myPacket = null;
  	   //byte[] buffer = new byte[100];
    	byte[] sizeOfFile = new byte[9];
		sizeOfFile = ("TNP"+Integer.toString(numberOfPackets)).getBytes() ;  		   
    	while(TNP_Ack==false)
		{
			Log.i("ss","TNP Sent. waiting for TNP-ACK");
			try {
				myPacket = new DatagramPacket(sizeOfFile, sizeOfFile.length);
				receivesocket.receive(myPacket)	;
				String tmp = new String(myPacket.getData());				
				if(tmp.equalsIgnoreCase("TNP"+Integer.toString(numberOfPackets))==true)
					TNP_Ack=true;
				else
				{
					Log.e("ss","Bad ack for TNP");
					Log.e("ss",tmp);
					Log.e("ss","TNP"+Integer.toString(numberOfPackets));
				}
				
			} catch (IOException e1) {
				Log.e("ss", "error in receiving TNP-ack");
			}
		}
    	
    	Log.e("ss","Server Listener :TNP Acked");
    	Log.i("ss","Server Listener Hoooora");
    	
    }
   
    public void clientSenderFunction ()		// Send Request again and again
   {
		//Send Message To Server
		DatagramPacket myreceivePacket = null;
		byte[] buffer = null;
		buffer = new byte[100];
		buffer = fileName.getBytes();
		// Sending Reuqest
		requestDelivered = false;
		try {
			myreceivePacket = new DatagramPacket(buffer, buffer.length,
					InetAddress.getByName("10.0.2.2"),3000);
			while(!requestDelivered )
			{
				Log.i("ss", "Sending request...");
				output += ("Sendign File Request: "+fileName+"\n");
				sendsocket.send(myreceivePacket)	;
				
				try { // wait 100ms and loop again | Send until ack recieved by ClientListener
					Thread.sleep(4000);
				} catch (InterruptedException e) {
					e.printStackTrace();
					Log.e("ss", "send thread sucked");
				}
				
			}
		} catch (IOException e) {
			Log.e("ss", "error in sending" + e.getMessage());
		}
		Log.e("ss", "Request Delivered ( send + ack) !");
		Log.i("ss", "ClientSender Hoooora");
   }
    
   public void clientFunction() throws IOException
   {
	   DatagramPacket myPacket = null;
	   byte[] buffer = null;
	   buffer = new byte[packetSizeByte];
	   myPacket = new DatagramPacket(buffer, buffer.length);
	   fileName = filename_st.getText().toString();
	   output += ("File: "+fileName+"\n");
	   
	   
	   numberOfPackets=-1; //unknown
	   
	   myClientSenderThread.start();
	   
	   // Loop until: Recieve TNP( and send back Its ack )
	   // and get first none-TNP packet which show that my Ack is deliverd to server
	   while( true  )
	   {
		   // Listening for request ack
		   Log.i("ss","i'm Listening for request ack");
		   myPacket = new DatagramPacket(buffer, buffer.length);
		   receivesocket.receive(myPacket)	;
		   		   
		   //Log.i("ss","is This TNP? :"+new String(myPacket.getData()));
		   String tmp = new String(myPacket.getData());
		   
		   if(requestDelivered==true && tmp.startsWith("TNP")==false )
		   {
			   //dataReceivingStarted=true;
			   Log.i("ss","YEAH ! First Data Packet Receved ! ");
			   break;//end loop to analyse first Data packet that received and continue to received
		   }
			   
		   if(tmp.startsWith("TNP")==true)
		   {
			   // This is ack from server, that contains total packet numbers
			   try{
				numberOfPackets = Integer.parseInt(tmp.substring(3, myPacket.getLength()));
				output += ("TNP Received.TNP="+numberOfPackets+"\n");
				requestDelivered=true;
				Log.i("ss","Acking TNP..");
				myPacket = new DatagramPacket(myPacket.getData(), myPacket.getLength(),
						InetAddress.getByName("10.0.2.2"),3000);
				sendsocket.send(myPacket);
				Log.i("ss","TNP ACKed");
				output += ("TNP responsed. waiting for packets...\n");
			   }catch(NumberFormatException e){
				   Log.e("ss","Bad Int in packet from server.. unknown Total Number of packets");				   
			   }
				
				   
		   }
		   
	   }// end of while(!requestDelivered) ==> Request Delivered ( send + ack)
	   Log.i("ss","Client Hoooora");
	   
	   
	   //Start Client Timer
	   alarmerThread	= new Thread( new Runnable() {
			@Override public void run() { ClientAlarmerFunction();}
		});
	   alarmerThread.start();
	   
	   numberOfRemainingPackets = numberOfPackets ;
	   packetsStatus = new boolean[numberOfPackets];
	   fileData = new byte[numberOfPackets][];
	   for(int i=0; i<numberOfPackets; i++)
		   packetsStatus[i]=false; // assume no packet has received
	   String seqNum_string=null;
	   int seqNum_int=-1;
	   myPacket = new DatagramPacket(buffer, buffer.length); //for sure
	   while( true )// Start Receiving 
	   {
		   seqNum_int=-1;
		   seqNum_string=null;
		  // Log.i("ss","Arrival PACKET SIZE IS:"+myPacket.getLength());
		//   Log.i("ss","Arrival PACKET IS:"+new String(myPacket.getData()));
		   //Extract Info
		   seqNum_string = (new String(myPacket.getData())).substring(0,6);
		 //  Log.i("ss","Processing INT:"+seqNum_string);
		   try{ seqNum_int = Integer.parseInt(seqNum_string); }
		   catch (NumberFormatException e){
			   Log.e("ss","BAD INT in Received Packet");
			   seqNum_int=-1;
		   }
		   
		   if(errorPosibility==true && r.nextInt(2)==1) //50% 
			   seqNum_int=-1;
		   
		   if(seqNum_int!=-1 && packetsStatus[seqNum_int]==false){
			   Log.i("ss","GOT Package#"+seqNum_int);
			   packetsStatus[seqNum_int]=true;
			   numberOfRemainingPackets--;
			   output += ("#"+seqNum_int+" OK!     Remained:"+numberOfRemainingPackets+"\n");
			   fileData[seqNum_int] = new byte[myPacket.getLength()-6];
			   
			   // fileData[seqNum_int] = myPacket.getData() ; // Wrong Totally
			   for(int i=6;i<myPacket.getLength()-1;i++)
				   fileData[seqNum_int][i-6]= (myPacket.getData())[i];
		   }
		   
		   if(numberOfRemainingPackets <= 0)
			   break; // AlL GOT
		   
		   //Listen for Another Packet
		   Log.i("ss","Remaining:"+numberOfRemainingPackets+"|Listening fot next packet..");
		   
		   //Reset Timer 
		   timeToSendList=false;

		   receivesocket.receive(myPacket)	;
	   }
	   buffer = new byte[4];
	   String ending="DONE";
	   buffer = ending.getBytes();
	   myPacket = new DatagramPacket(buffer, buffer.length,
				InetAddress.getByName("10.0.2.2"),3000);
		sendsocket.send(myPacket);
	   Log.i("ss","HHHHHHHHHHHHHHHHHHHHHHHOOOOOOORA!!");
	   output += ("------------------\n-----------------\n ALL DONE !");
	   
	   //Writing on file
	   output += "Writing on SD Card... \n";
		File myFile=new File(Environment.getExternalStorageDirectory().getPath()+"/_"+fileName);
		RandomAccessFile raf=null;		
		try{
			myFile.createNewFile();
			raf=new RandomAccessFile(myFile, "rw");			
		}catch(Exception e){
			Log.e("ss","File Creation Error+ "+ e.getMessage());
		}
		
	   for(int i=0;i<numberOfPackets;i++)
	   {
		   Log.i("ss","fileData["+i+"]Size:"+fileData[i].length);
		   try{
			raf.write(fileData[i]);	
		   }catch(Exception e){
			   Log.e("ss","Error in Write File "+ e.getMessage());
		   }
	   }
	   raf.close();
	   allDone=true;
	   output += "You can Play It... \n";	  
   
   }
   
   public void ClientAlarmerFunction()
   {
		byte[] buffer = new byte[AlarmMessageLength];
		DatagramPacket myPacket = null;
	   while(numberOfRemainingPackets>0)
	   {
		   if(timeToSendList)
		   {
			   Log.i("ss","Time To Send");
			   timeToSendList=false;
			   // Create Message
	   			String tmp="";
	   			for(int i=0;i<numberOfPackets;i++)
	   				if(packetsStatus[i]==false)
	   					tmp += (Integer.toString(i)+"*");
	   			output += (tmp+"\n") ;
	   			if(tmp.length()>AlarmMessageLength)
	   			{
		   			output += "\nLONG ACK Breaked";
		   			int c=tmp.lastIndexOf('*',AlarmMessageLength);
		   			tmp = tmp.substring(0, c-1);
		   			output += ("\nBreaked=>"+tmp);
	   			}
	   		// 	Done
	   			buffer = tmp.getBytes();
	   			
	   			try {
					myPacket = new DatagramPacket(buffer, buffer.length,
							InetAddress.getByName("10.0.2.2"),3000);
				} catch (UnknownHostException e) {
					Log.e("ss","UNKONW HOST in Send LIST:"+e.getMessage());
					e.printStackTrace();
				}
   				//Log.i("ss","lll===>"+myPacket.getLength());
				//Log.i("ss","lll===>"+new String(myPacket.getData()));
	   			try {
					sendsocket.send(myPacket);
				} catch (IOException e) {
					Log.e("ss","SEND Cant Send LIST:"+e.getMessage());
					e.printStackTrace();
				}
	   			Log.i("ss","List SSSSSSSSSSSENT !!");
		   }
		   else
		   {
			   timeToSendList=true; //if nobody false it, after wait() we understand we should send list
		   }
		   
		   try {
				Thread.sleep(sendNotdeliverdTimerTime);
			} catch (InterruptedException e) {
				e.printStackTrace();
				Log.e("ss", "send thread sucked");
			}
		   
	   }
   }
}