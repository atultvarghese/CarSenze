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

            throw new UnsupportedOperationException("Not yet implemented");
    }
}