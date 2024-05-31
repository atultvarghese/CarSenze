package com.randstad.carsenze;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.RemoteException;

public class CarSenzeService extends Service {
    public CarSenzeService() {
    }

    @Override
    public IBinder onBind(Intent intent) {
          return Binder;
              /*throw new UnsupportedOperationException("Not yet implemented");*/
    }
    private final IStatsService.Stub Binder= new  IStatsService.Stub(){


        @Override
        public String getCpuStats() throws RemoteException {
            return "";
        }

        @Override
        public String getMemoryStats() throws RemoteException {
            return "";
        }

        @Override
        public String getNetworkStats() throws RemoteException {
            return "";
        }
    };
}