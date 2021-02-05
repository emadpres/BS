package com.network.eawifi;

import java.io.File;

import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.MediaController;
import android.widget.TextView;
import android.widget.VideoView;

public class Third extends Fragment{

	static int size;					//video size
	static String targetAdd=null;
	private File f;						//receive file
	static VideoView v;
	boolean Play=false;					//play flag
	boolean First_time=true;		//flag to check is it first try to play?
	boolean First_time_b=true;
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View view=inflater.inflate(R.layout.third_layout,container,false);
		
		v = (VideoView) view.findViewById(R.id.videoView1);;
		MediaController mc = new MediaController(getActivity());
		v.setMediaController(mc);
		mc.setEnabled(false);
		han.post(r);
		return view;
	}
	
	private Handler han=new Handler();
	private Runnable r=new Runnable() {
		
		@Override
		public void run() {

			if(targetAdd!=null && targetAdd!="")
			{
				//Second.logString += ("targetAdd:"+targetAdd+"\n");
				if(First_time_b){
					Log.i("MMM","FirstTime_b");
	       			f=new File(targetAdd);
	       			First_time_b=false;
				}
				
				
				if(First_time && ((float)f.length()/size) > 0.4 ){		//check for receive more than 20%
					Second.logString += ("\nPLAY:"+targetAdd+"\n\n");
					Log.i("MMM"," >>>> PLAY START <<<< ");
					Log.i("MMM","recieved Size: "+f.length());
					Log.i("MMM","Total Size: "+size);
					Log.i("MMM","Ratio : "+ ((float)f.length()/size)  );
					v.setVideoPath(targetAdd);
					v.start();
					Play=true;
					First_time=false;
				}
				else if(First_time)
				{
					Log.i("MMM","lack of data of:"+targetAdd);
					Log.i("MMM","R:"+f.length()+" T:"+size+" Ra:"+ ((float)f.length()/size) );
					//Second.logString += ("+ "+((float)f.length()/size)+"\n");
				}
				else
				{
					Log.e("MMM","It's at play");
				}
				
				if(Play && ((float)v.getCurrentPosition()/v.getDuration())+0.4 > ((float)f.length()/size)){		//5% Tolerance 
					Log.e("MMM","Pause");
					Second.logString += ("\n Auto Pause \n");
					/*Second.logString += ("Current:"+v.getCurrentPosition()+"\n");
					Second.logString += ("Total:"+v.getDuration()+"\n");
					Second.logString += ("R:"+(float)v.getCurrentPosition()/v.getDuration()+"\n");
					Second.logString += ("SIZE BASE\n");
					Second.logString += ("R:"+f.length()+" T:"+size+" Ra:"+ ((float)f.length()/size)+"\n");*/
					v.pause();
					Play=false;
				}
				else
				{
					/*if(Play)
					{
						Second.logString += ( v.getCurrentPosition()+" of "+v.getDuration()+"\n");
						Second.logString += ("Until Pause:"+ (((float)v.getCurrentPosition()/v.getDuration())-((float)f.length()/size) ) + "\n" );
					}*/
					Log.i("MMM",v.getCurrentPosition()+"|"+v.getDuration()+"|"+(v.getCurrentPosition()/v.getDuration())+"|"+((float)f.length()/size));
				}
				
				if( !Play && !First_time && ( ((float)v.getCurrentPosition()/v.getDuration())+0.5 < ((float)f.length()/size)   || ((float)f.length()/size)>=1 ) ) {		//10% tolerance
					Log.e("MMM","Resume");
					Second.logString += ("\n Auto Resume \n");
					/*Second.logString += ("Current:"+v.getCurrentPosition()+"\n");
					Second.logString += ("Total:"+v.getDuration()+"\n");
					Second.logString += ("R:"+(float)v.getCurrentPosition()/v.getDuration()+"\n");
					Second.logString += ("SIZE BASE\n");
					Second.logString += ("R:"+f.length()+" T:"+size+" Ra:"+ ((float)f.length()/size)+"\n");*/
					v.start();
					Play=true;
				}
			}
			else if(targetAdd==null)
				Log.i("MMM","No Address to play yet: NULL");
			else if(targetAdd=="")
				Log.i("MMM","No Address to play yet: \"\" ");
			else
				Second.logString += ("?????\n");
			//if(targetAdd=="")
			han.postDelayed(r, 2000L);
			//else
				//han.postDelayed(r, 100L);
		}
	};

}
