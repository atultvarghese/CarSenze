package com.randstad.carsenze;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {

    private IStatsService iStatsService;

    private ServiceConnection serviceConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            iStatsService = IStatsService.Stub.asInterface(service);

            try {
                TextView memory = findViewById(R.id.memory);
                memory.setText(iStatsService.getMemoryStats());

                TextView cpu = findViewById(R.id.cpu);
                cpu.setText(iStatsService.getCpuStats());

                TextView network = findViewById(R.id.network);
                network.setText(iStatsService.getNetworkStats());
            } catch (RemoteException e){
                e.printStackTrace();
            }

        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            iStatsService = null;
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
      // EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        bindService(new Intent(this, CarSenzeService.class), serviceConnection, Context.BIND_AUTO_CREATE);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unbindService(serviceConnection);
    }
}