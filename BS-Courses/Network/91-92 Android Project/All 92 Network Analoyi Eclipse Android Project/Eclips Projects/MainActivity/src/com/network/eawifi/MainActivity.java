package com.network.eawifi;

import com.network.eawifi.First.sendData;

import android.os.Bundle;
import android.app.Activity;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.Menu;

public class MainActivity extends FragmentActivity implements sendData {

	ViewPager vp;
	SectionViewChanger svc;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		svc=new SectionViewChanger(getSupportFragmentManager());
		vp=(ViewPager) findViewById(R.id.main_layout);
		vp.setAdapter(svc);
	}
	
	@Override
	public void requestTosendLog(String str) {
//		Second s=new Second();
//		s=(Second) svc.getItem(1);
		//second.AppendTextToLog(str);
		//second.AppendTextToLog("\n"+str);
		Second.logString+="\n"+str;
		
	}
	
	public class SectionViewChanger extends FragmentPagerAdapter {

		public SectionViewChanger(FragmentManager fm) {
			super(fm);
			// TODO Auto-generated constructor stub
		}

		@Override
		public Fragment getItem(int arg0) {
			switch(arg0){
			case 0 :
				return new First();
			case 1:
				return new Second();
			case 2:
				return new Third();
			}
			return null;
		}

		@Override
		public int getCount() {
			return 3;
		}

		@Override
		public CharSequence getPageTitle(int position) {
			switch(position){
			case 0:
				return "First";
			case 1:
				return "Second";
			case 2:
				return "Third";
			}
			return super.getPageTitle(position);
		}
		
		
	}

}
