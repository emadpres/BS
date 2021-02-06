package com.network.eawifi;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.io.SequenceInputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Random;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.TextView;

public class First extends Fragment implements OnClickListener{
	
	public interface sendData{
		void requestTosendLog(String str);
	}
	sendData send;
	
	int K, packetSize;
	//TextView sfile;
	RadioButton r1=null, r2=null;
	EditText errorRate_et=null, fileName_et=null, PacketSize_et=null;
	Button startBtn, sfile;
	CheckBox uploadMode_ch;
	
	int HEADER_OFFSET = 1 ;
	byte[] END_BYTE= "+_+_+".getBytes();
	int ERR_RATE = 0;
	
	boolean stopSend=false; //stopRecieve=false,
	boolean socketInitialize=false;
	
	String targetFileName;  // <------------ TARGET FILE NAME
	byte[][] data; 			// <------------ DATA ARRAY
	
	Thread thread_RecieveFile = null;
	Thread thread_BGNSendData = null;
	Thread thread_BGNACK = null ;
	Thread thread_SendFile = null ;
	
	DatagramSocket sendSocket = null;
	int SEND_PORT_SERVER = 6000 , SEND_PORT_CLIENT=7000 ;
	DatagramSocket receiveSocket = null ;
	int RECEIVE_PORT_SERVER = 7000, RECEIVE_PORT_CLIENT=6000 ;
	
	DatagramPacket newPacket_send=null, newPacket_received=null;
	byte[] newPacketBuffer_received=null; //send use 'data'
	
	int expectedPackNum=0, base=0, nextPack=0 , windowSize=10; // BGN
	
	int dataNumber = -1 ; // just file
	int totalSize= -1 ; // in Byte  || 'totalSize' for receiver in first packet
	int totalPacket = -1; // file + header + ender
	int SeqNumOfByte=2; // max packet number : 2 ^ 16 
	byte[] packNum_byte = null;	 // use to attach packet's seqNumber
	Random r=null;
	private Handler ackTimer_handler;
	private int ackTimer_interval = 100, sendTimer_interval=5;

	
	@Override
	public void onAttach(Activity activity) {
		try{
			 send=(sendData) activity;
		}catch(Exception e){
			throw new ClassCastException("not implements " + e.getMessage().toString());
		}
		super.onAttach(activity);
	}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View view = inflater.inflate(R.layout.first_layout, container, false);
		
		ackTimer_handler = new Handler();
		targetFileName = "" ;
		r = new Random();
		
		//fileName_EditText
		sfile=(Button) view.findViewById(R.id.first_select);
		startBtn=(Button) view.findViewById(R.id.first_send);
		r1 = (RadioButton) view.findViewById(R.id.first_radio_client);
		r2 = (RadioButton) view.findViewById(R.id.first_radio_server);
		PacketSize_et= (EditText )  view.findViewById(R.id.packetSize_EditText);
		errorRate_et= (EditText )  view.findViewById(R.id.packet_text);
		fileName_et= (EditText ) view.findViewById(R.id.fileName_EditText);
		uploadMode_ch = (CheckBox) view.findViewById(R.id.uploadMode_ch);
		Third.targetAdd="";
		
		Log.i("EMAD","Initialed On Create");
		sfile.setOnClickListener(this);
		startBtn.setOnClickListener(this);
		return view;
	}

	@Override
	public void onClick(View v) {
		if(v.getId() == R.id.first_select) {
			Intent intent=new Intent(getActivity(),SelectFileDialog.class);
			startActivityForResult(intent, 1);
		}
		else if(v.getId() == R.id.first_send) {
			
			if(socketInitialize)
				return;
		
			if( r1.isChecked() && !uploadMode_ch.isChecked())
			{
				targetFileName = fileName_et.getText().toString();
				if( targetFileName=="" ) //Client + !UploadMode + ""
				{			
					fileName_et.setText("Select a File");
					return;
				}
			}			
			
			socketInitialize=true;
			
			ERR_RATE = Integer.parseInt(errorRate_et.getText().toString());
			packetSize = Integer.parseInt(PacketSize_et.getText().toString());
			K=packetSize-SeqNumOfByte;
			
			packNum_byte = new byte[SeqNumOfByte];
			newPacketBuffer_received = new byte[SeqNumOfByte+K] ; // <--- packet structure 
			newPacket_received  = new DatagramPacket(newPacketBuffer_received , newPacketBuffer_received.length);
						
			if(r1.isChecked()) //client
			{
				try{
					receiveSocket =new DatagramSocket(RECEIVE_PORT_CLIENT);
					sendSocket =new DatagramSocket(SEND_PORT_CLIENT);
				}catch(Exception e){
					Log.e("EMAD","Socket Creation Error  "+ e.getMessage());
				}
				
				//sfile.setText("Listening...");
				thread_RecieveFile = new Thread(new Runnable() {
					@Override public void run() {threadFunc_RecieveFile();}
				});
				thread_RecieveFile.start();				
			}
			else //server
			{
				try{
					receiveSocket =new DatagramSocket(RECEIVE_PORT_SERVER);
					sendSocket =new DatagramSocket(SEND_PORT_SERVER);
				}catch(Exception e){
					Log.e("EMAD","Socket Creation Error  "+ e.getMessage());
				}
				
				//sfile.setText("Sending...");
				thread_SendFile = new Thread(new Runnable() {
					@Override public void run() { threadFunc_SendFile(); }
				});
				thread_SendFile.start();				
			}
						
			
		}
		
	}

	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		if(requestCode ==1){
			//sfile.setText(data.getExtras().getString("get"));
			targetFileName = data.getExtras().getString("get") ;
			Second.logString += ("Selected File:"+targetFileName+"\n"); // bad : target is total path not just name
		}
		super.onActivityResult(requestCode, resultCode, data);
	}

	private void threadFunc_RecieveFile(){
		
		boolean allGot=false, firstTime=true;
		byte[] newPacketBuffer_send = new byte [100] ;
		newPacketBuffer_send[0] = (byte) ( 0 ) ; //first 
		newPacketBuffer_send[1] = (byte) ( 0 ) ;
		int extractPacketNumber = 0 ;
		
		if(uploadMode_ch.isChecked()==false)
		{
			Log.i("EMAD","Sending File Name As request");
			newPacketBuffer_send = targetFileName.getBytes();
			try {
				newPacket_send = new DatagramPacket(newPacketBuffer_send, newPacketBuffer_send.length,
						InetAddress.getByName("10.0.2.2"), SEND_PORT_CLIENT );
				sendSocket.send(newPacket_send);
			} catch (Exception e) {
				Log.e("EMAD","Error in Sendin File Name"+e.getMessage());
			}
			
			Log.i("EMAD","Request Sent");
		}
			
		File rcvFile=new File(Environment.getExternalStorageDirectory().getPath()+"/Rcv_"+targetFileName);
		RandomAccessFile raf=null;		
		try{
			rcvFile.createNewFile();
			raf=new RandomAccessFile(rcvFile, "rw");			
		}catch(Exception e){
			Log.e("EMAD","File Creation Error+ "+ e.getMessage());
		}
				
		Log.e("EMAD" , "Starting While(!allGot)" );
		/************************************************************* MAIN LOOP */ 
		newPacketBuffer_send = new byte [SeqNumOfByte] ;
		while(!allGot)
		{
			/*try {
				Thread.sleep(5000);
			} catch (InterruptedException e) {
				e.printStackTrace();
				Log.e("EMAD", "send thread sucked");
			}*/
			
			Log.i("EMAD" , "Listen/Expecting for "+expectedPackNum );
			try{
				
				if(!firstTime) //ACK 
				{
				newPacket_send = new DatagramPacket(newPacketBuffer_send, newPacketBuffer_send.length,
												InetAddress.getByName("10.0.2.2"), SEND_PORT_CLIENT );
				sendSocket.send(newPacket_send);
				}
				else
				{
					firstTime=false;
					Second.logString += ("Ready to receive ... \n");
				}
				
				receiveSocket.receive(newPacket_received);
							
				// check Seq Num
				packNum_byte[0]=newPacket_received.getData()[0];
				packNum_byte[1]=newPacket_received.getData()[1];
				extractPacketNumber = 0 ;
				extractPacketNumber = ((packNum_byte[1]&0xFF)<<8) + (packNum_byte[0]&0xFF) ;
				Log.i("EMAD","Received Packet : "+extractPacketNumber );
					
				if( r.nextInt(100)<ERR_RATE)
					extractPacketNumber = -1 ;
				
				if(extractPacketNumber == expectedPackNum )
				{
				   	Second.logString += ("Got #"+extractPacketNumber+"\n");
					expectedPackNum++ ;
					newPacketBuffer_send[0] = (byte)expectedPackNum ;
					newPacketBuffer_send[1] = (byte)(expectedPackNum>>8);
					if(extractPacketNumber==0)
					{
						Log.i("EMAD","Found First Packet");
						//Processing HEADER
					   	String tmp = new String(newPacket_received.getData());
					   	try{
					   	totalSize = Integer.parseInt(tmp.substring(SeqNumOfByte,newPacket_received.getLength()));
					   	}catch(NumberFormatException e) // catch Invalid Int
					   	{
					   		Log.e("EMAD","BAD INT SIZE");
					   		expectedPackNum--; // bad header
					   	}
					   	Second.logString += ("File size: "+totalSize+"\n");
					   	data = new byte[ (int)(totalSize/K )+1+ HEADER_OFFSET +1 ][]; //
					   	Third.size = totalSize ;		 // ?
					   	Log.e("LL","Third.target set:"+Third.targetAdd);
					   	Third.targetAdd = rcvFile.getPath().toString();
					   	Log.e("LL","Third.target set:"+Third.targetAdd);
					   	Second.logString += ("Stream on "+Third.targetAdd+"\n");
					   	//Third.targetAdd = targetFileName;
					   	Log.i("EMAD","TotalSize in Bytes: "+totalSize);
					   	//raf.setLength(5000);
			        	//raf.setLength(Integer.parseInt(tmp.substring(0,pack.getLength())));  
					   	//Third.v.setVideoPath(rcvFile.getPath().toString());
					   	continue;
					}
				}
				else
				{
					newPacketBuffer_send[0] = (byte)expectedPackNum ;
					newPacketBuffer_send[1] = (byte)(expectedPackNum>>8);
					continue;
				}
				
				//correct new packet
				Log.i("EMAD","length="+newPacket_received.getLength());
				//sample Show
				String tmp2 = new String(newPacket_received.getData());
				if(newPacket_received.getLength()<20)
					tmp2 = tmp2.substring(SeqNumOfByte, newPacket_received.getLength());
				else
					tmp2 = tmp2.substring(SeqNumOfByte,20);
		        Log.i("EMAD","INFO>>"+ tmp2 );
				//update Log
				if(totalSize!=-1)
					Second.progressValue = (expectedPackNum*100 / ((totalSize/K)+3) ) ; 
				//send.requestTosendLog("Got Packet "+extractPacketNumber);
				//check if ENDER
				if(newPacket_received.getLength()-SeqNumOfByte == END_BYTE.length)
				{
					 Log.i("EMAD","Check Last Byte-ility");
					 allGot=true; 
			        for(int j=0; j<END_BYTE.length; j++)
			        {
				       if( newPacket_received.getData()[j+SeqNumOfByte]!= END_BYTE[j])
				       		allGot=false; 
			        }
				}
				if(allGot)
					break; // Let's go ack ending

				
				// Normal Packet
				data[extractPacketNumber-HEADER_OFFSET] = new byte[newPacket_received.getLength()-SeqNumOfByte];
				for(int j=0;j<newPacket_received.getLength()-2;j++)
					data[extractPacketNumber-HEADER_OFFSET][j] = newPacket_received.getData()[j+2];	
				
	
			}catch(Exception e){
				Log.e("EMAD","Error in Recieve Data "+ e.getMessage());
			}
			
			
			try{
				Log.i("EMAD","Writing Packet Number "+extractPacketNumber+" - "+HEADER_OFFSET);
				raf.write(data[extractPacketNumber-HEADER_OFFSET]);	
				
			}catch(Exception e){
				Log.e("EMAD","Error in Recieve And Write File "+ e.getMessage());
			}
		
		} //end WHILE
		
		// All Got
		Log.e("EMAD" , "Ending Received File After writing last "+newPacket_received.getData().length+" Bytes" );
    	
		Second.logString += ("Receive Done Successfully!\n");

		
    	try{
        	raf.close();
		}catch(Exception e){
			Log.e("EMAD","Error in Closing Received File :(("+ e.getMessage());
		}
    	
    	
		
    	// Final Ack
    	Log.i("EMAD", "ACKING ENDER");
    	try{
    	newPacket_send = new DatagramPacket(newPacketBuffer_send, newPacketBuffer_send.length,
				InetAddress.getByName("10.0.2.2"), SEND_PORT_CLIENT );
    	sendSocket.send(newPacket_send);
    	}catch(Exception e){
			Log.e("EMAD","Error in FINAL ACK"+ e.getMessage());
		}
		
    	
    	
	}// end ThreadFunc
	
	private void threadFunc_SendFile() 	// Make Data from source File
	{
		File source=null;
		FileInputStream fis = null ;
		if(targetFileName!="") //upload mode
		{
			Log.i("EMAD","Opening for upload this:"+targetFileName);
			source=new File(targetFileName);
			try {
				fis = new FileInputStream(source);
			} catch (FileNotFoundException e) {
				Log.e("EMAD","Cant open file"+e.getMessage());
				Second.logString += ("File Not Found:\n"+source.getPath().toString()+"\n") ;
				Second.logString += ("For Sure reset program!");
				}
		}
		while(targetFileName=="")
		{
			Second.logString += "Waiting...\n" ;
			try {
				receiveSocket.receive(newPacket_received);
			} catch (IOException e) {
				Log.e("EMAD","CANT Receive File Name"+e.getMessage());
			}
			targetFileName = (new String (newPacket_received.getData())).substring(0,newPacket_received.getLength());
			source=new File(Environment.getExternalStorageDirectory().getPath()+"/"+targetFileName);
			try {
				fis = new FileInputStream(source);
			} catch (FileNotFoundException e) {
				Log.e("EMAD","Cant open file"+e.getMessage());
				Second.logString += ("File Not Found:\n"+source.getPath().toString()+"\n") ;
				targetFileName="";
			}
		}
		Log.e("EMAD", "Starting Sepration");
		Second.logString += ("Creting File Data\n");
		
	
		// Intial
		Log.i("EMAD","Requested File Name:"+source.getName());
		Log.i("EMAD","Requested File Size:"+source.length());
		dataNumber = (int)((source.length()/K));
		if(source.length()>dataNumber*K)
			dataNumber++; // dataNumber : Number of just-File Parts ( including last partial part)
		Log.i("EMAD"," Total Part ~~~>  "+ dataNumber); 
		
		totalPacket = HEADER_OFFSET + dataNumber + 1;
		data = new byte[totalPacket][];
		
		// Seq Number Start from First Data packet and include ENDER even !
		// So, HEADER has not seq number. It qualify in destination as reequest
		
		// 1/3 Headering
		HEADER_OFFSET = 1 ; // number of header byte[] for sync
		Log.i("EMAD"," Total Bytes ~~~> "+ source.length() );
		data[0] = new byte[Integer.toString((int) source.length()).getBytes().length+SeqNumOfByte];
		
		byte tmp[] = Integer.toString((int) source.length()).getBytes() ; // 'totalSize' for receiver
	//	Log.i("EMAD"," TMP: "+new String(tmp));
		//Log.i("EMAD"," TMP Len:"+tmp.length);
		packNum_byte[0] = (byte) (0) ;
		packNum_byte[1] = (byte) (0) ;
		data[0][0] = packNum_byte[0] ;
		data[0][1] = packNum_byte[1] ;
		for(int j=0;j<tmp.length;j++)
			data[0][j+2] = tmp[j];

		
		// 2/3 Main File

		for(int i=0;i< dataNumber-1 ;i++){
			
			packNum_byte[0] = (byte) ((i+HEADER_OFFSET)&0xFF) ;
			packNum_byte[1] = (byte) (((i+HEADER_OFFSET)>>8)&0xFF) ;
			
			try {
			//	Log.i("EMAD","Demux part"+i);
				data[HEADER_OFFSET + i] = new byte[K+SeqNumOfByte];
				fis.read(data[HEADER_OFFSET + i], SeqNumOfByte , K);
				data[HEADER_OFFSET + i][0] = packNum_byte[0] ;
				data[HEADER_OFFSET + i][1] = packNum_byte[1] ;
			} catch (IOException e) {
				e.printStackTrace();
			}
			//data[i]=ReadFile(source, i*K, K);
		}
		
		
		try { // last file part
			data[HEADER_OFFSET + dataNumber-1] = new byte[(int) source.length()-(dataNumber-1)*K + SeqNumOfByte];
			fis.read( data[HEADER_OFFSET + dataNumber-1], SeqNumOfByte , (int) source.length()-(dataNumber-1)*K);
			packNum_byte[0] = (byte) ((dataNumber-1+HEADER_OFFSET)& 0xFF) ;
			packNum_byte[1] = (byte) (((dataNumber-1+HEADER_OFFSET)>>8) & 0xFF) ;
			data[HEADER_OFFSET + dataNumber-1][0] = packNum_byte[0] ;
			data[HEADER_OFFSET + dataNumber-1][1] = packNum_byte[1] ;
			fis.close();
			
		} catch (IOException e) {
			Log.e("EMAD"," Creating Data Error "+ e.getMessage() );
		}
		
		
		// 3/3 Ender
		data[HEADER_OFFSET + dataNumber] = new byte[SeqNumOfByte+END_BYTE.length];
		packNum_byte[0] = (byte) ((dataNumber+HEADER_OFFSET)& 0xFF) ;
		packNum_byte[1] = (byte) (((dataNumber+HEADER_OFFSET)>>8)& 0xFF) ;
		data[HEADER_OFFSET + dataNumber][0] = packNum_byte[0] ;
		data[HEADER_OFFSET + dataNumber][1] = packNum_byte[1] ;
		for(int j=0;j<END_BYTE.length;j++)
			data[HEADER_OFFSET + dataNumber][j+2] = END_BYTE[j];
		
		
		Log.i("EMAD","Data[] Done with # :"+totalPacket+" Packets");
		Second.logString += ("File Data Created !\n Starting Sending.");
		
		thread_BGNSendData = new Thread(new Runnable() {
			@Override public void run() {threadFunc_BGNSendData();}
		});
		thread_BGNSendData.start();
		
		thread_BGNACK = new Thread(new Runnable() {
			@Override public void run() {threadFunc_BGNACK();}
		});
		thread_BGNACK.start();
		

	}
	
	private void threadFunc_BGNACK()
	{
	//	DatagramPacket pack = null ;
	//	byte[] temp = new byte [100] ;
	//	byte[] packNum_byte=new byte[2];
		int ackedNumber;
		
		/*try{
			receiveSocket=new DatagramSocket(SEND_PORT);
			pack=new DatagramPacket(temp, K);
		}catch(Exception e){
			Log.e("EMAD","Socket ACK Creation Error+ "+ e.getMessage());
		}*/
		
		
		while(true){
			try{
				receiveSocket.receive(newPacket_received);
				
				packNum_byte[0]=newPacket_received.getData()[0];
				packNum_byte[1]=newPacket_received.getData()[1];
				
				Log.i("EMAD","ACK 1>"+((int) packNum_byte[1]) );
				Log.i("EMAD","ACK 0>"+((int) packNum_byte[0]) );
				
				
				ackedNumber = ((packNum_byte[1]&0xFF)<<8) + (packNum_byte[0]&0xFF) ;
				
				/*ackedNumber = (int) packNum_byte[1] ;
				ackedNumber = (ackedNumber<<8);
				Log.i("EMAD","ACK 0>>"+ackedNumber );
				
				ackedNumber = (int) packNum_byte[1] ;
				Log.i("EMAD","ACK 0>>"+ackedNumber );
				
				ackedNumber = (int) packNum_byte[0] ;
				Log.i("EMAD","ACK 0>>"+ackedNumber );
				
				Log.i("EMAD","ACK 1>>"+((int) 0x00FF &  packNum_byte[1]) );
				ackedNumber = (ackedNumber<<8) + (int) packNum_byte[0] ;*/
				Log.i("EMAD" , "ACK Received : "+ackedNumber );

				if(ackedNumber == totalPacket)
				{
					Log.e("EMAD","ackedNumber > totalPacket "+ackedNumber+" "+totalPacket );
					stopSend=true;
					Second.logString += ("last packet Ack received !");
					Second.logString += ("\nSend Done Successfully!\n");
					ackTimer_handler.removeCallbacks(ackUpdate);
					Log.i("EMAD"," SEND Stoped ..  ! B-) ");
				}
				if( base < ackedNumber)
				{
					base = ackedNumber  ;
					//reset Ack Timer
					ackTimer_handler.removeCallbacks(ackUpdate);
					ackTimer_handler.postDelayed(ackUpdate, ackTimer_interval);
					// Update progress Bar
					Second.progressValue = (ackedNumber*100 / totalPacket ) ;
				}
				
			}catch(Exception e){
				Log.e("EMAD","ACK Recieve Error+ "+ e.getMessage());
			}
		}
	}
	
	private void threadFunc_BGNSendData()
	{
		while( !stopSend )
		{
			//Log.i("EMAD","SEND LOOP. nextPack:"+nextPack+"  base:"+base);
			if( nextPack < (base + windowSize) && nextPack<totalPacket)
			{
					
				Log.i("EMAD" , "Sending packet "+nextPack );
				Second.logString += ("Sending #"+nextPack+"\n");
				try {
					newPacket_send = new DatagramPacket( data[nextPack], data[nextPack].length,  
														InetAddress.getByName("10.0.2.2"), SEND_PORT_SERVER );
					sendSocket.send(newPacket_send);
				}catch (Exception e) {
					Log.e("EMAD", "Cant Send Data #"+ nextPack + e.getMessage());
					stopSend=true;
				}
				
				if(nextPack==base) { // reset ackTimer
					Log.e("EMAD", "Reseting AckTimeout Timer");
					ackTimer_handler.removeCallbacks(ackUpdate);
					ackTimer_handler.postDelayed(ackUpdate, ackTimer_interval);					 
				}
				
				nextPack++;
			}
			
			try {
				Thread.sleep(sendTimer_interval);
			} catch (InterruptedException e) {
				e.printStackTrace();
				Log.e("EMAD", "send thread sucked");
			}
		}
		
	}

	private Runnable ackUpdate=new Runnable() {
		
		@Override
		public void run() {
			if(!stopSend){
				nextPack=base;
				Second.logString += ("ack Timeout!\n");
				ackTimer_handler.postDelayed(ackUpdate, ackTimer_interval);
			}
		}
	};
	/*******************************************************************************/
	public byte[] ReadFile(File f, int offset, int count) {
		byte[] data = new byte[K];
		int l=-1;
		try {
			FileInputStream fis = new FileInputStream(f);
			Log.w("EMAD","FileInputStream Create "+offset);
			fis.skip(offset);
			if (fis != null) {
				Log.w("EMAD","==> "+l);
				l=fis.read(data, 0, count);
				fis.close();
			}
		} catch (Exception e) {
			Log.e("error in Reading...", e.getMessage().toString()+" / "+e.getLocalizedMessage().toString());
		}
		return data;
	}
	/*******************************************************************************/
	public void WriteFile(File f, byte[] data, int offset) {
		
		try {
			RandomAccessFile rf=new RandomAccessFile(f, "rw");
			rf.seek(offset);
			rf.write(data);
			rf.close();
//			FileOutputStream fos = new FileOutputStream(f);
//			fos.write(data, 0, data.length);
//			fos.flush();
//			fos.close();
		} catch (Exception e) {
			Log.e("error in writting...", e.getMessage().toString());
		}
	}
	/*******************************************************************************/
}
