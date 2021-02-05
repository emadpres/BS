package com.network.eawifi;

import android.os.Bundle;
import android.os.Handler;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;
import android.widget.TextView;

	

public class Second extends Fragment{

	static String logString;
	static int progressValue=0;
	TextView tv;
	ProgressBar  process = null ;
	
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View view=inflater.inflate(R.layout.second_layout, container,false);
		tv=(TextView) view.findViewById(R.id.second_log);
		process=(ProgressBar ) view.findViewById(R.id.second_progress);
		tv.setText(Second.logString);
		handler.postDelayed(update, 500L);
		progressValue=0;
		logString="";		
		return view;
	}
	
	private Handler handler=new Handler();
	private Runnable update=new Runnable() {
		
		@Override
		public void run() {
			tv.setText(Second.logString);
			process.setProgress(progressValue);
			//logString += ("\n==="+progressValue);
			handler.postDelayed(update, 500L);
			
		}
	};

}
