package com.randstad.carsenze;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.RemoteException;

import androidx.annotation.NonNull;
import androidx.car.app.CarContext;
import androidx.car.app.Screen;
import androidx.car.app.model.Action;
import androidx.car.app.model.Pane;
import androidx.car.app.model.PaneTemplate;
import androidx.car.app.model.Row;
import androidx.car.app.model.Template;

public class MainScreen extends Screen {
    public IStatsService iStatsService;
    private ServiceConnection serviceConnection = new ServiceConnection(){
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder iBinder) {
            iStatsService = IStatsService.Stub.asInterface(iBinder);
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            iStatsService = null;
        }
    };
    public MainScreen(@NonNull CarContext carContext) {
        super(carContext);
        carContext.bindService(new Intent(carContext, CarSenzeService.class), serviceConnection, Context.BIND_AUTO_CREATE);
    }

    @NonNull
    @Override
    public Template onGetTemplate() {
        Pane.Builder paneBuilder=new Pane.Builder();
        try {
            paneBuilder.addRow(new Row.Builder()
                    .setTitle("CPU Info:" + iStatsService.getCpuStats())
                    .build());
        } catch (RemoteException e) {
            throw new RuntimeException(e);
        }
        try {
            paneBuilder.addRow(new Row.Builder()
                    .setTitle("Memory Info:" + iStatsService.getMemoryStats())
                    .build());
        } catch (RemoteException e) {
            throw new RuntimeException(e);
        }
        try {
            paneBuilder.addRow(new Row.Builder()
                            .setTitle("Network Info:" + iStatsService.getNetworkStats())
                    .build());
        } catch (RemoteException e) {
            throw new RuntimeException(e);
        }

        return new PaneTemplate.Builder(paneBuilder.build()).setHeaderAction(Action.BACK).build();

    }
}
