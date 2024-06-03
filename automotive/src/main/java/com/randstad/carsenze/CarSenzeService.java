package com.randstad.carsenze;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

public class CarSenzeService extends Service {

    static {
        System.loadLibrary("carsenze");
    }

    public static native String memoryInfo();
    public static native String cpuInfo();
    public static native String networkStat();

    public CarSenzeService() {
    }

    @Override
    public IBinder onBind(Intent intent) {
          return Binder;
    }
    private final IStatsService.Stub Binder= new  IStatsService.Stub(){


        @Override
        public String getCpuStats() throws RemoteException {
            Log.e("myTag",cpuInfo());
            return cpuInfo();
        }

        @Override
        public String getMemoryStats() throws RemoteException {
            return memoryInfo();
        }

        @Override
        public String getNetworkStats() throws RemoteException {
            return networkStat();
        }
    };
}