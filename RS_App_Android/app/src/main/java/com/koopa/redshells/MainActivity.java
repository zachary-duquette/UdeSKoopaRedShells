package com.koopa.redshells;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;

import android.widget.TextView;

import java.util.Timer;

public class MainActivity extends Activity implements ServerListener
{
    /**
     * Constants*
     */
    final int PLAYER_NUMBER_BLUE = 1;
    final int PLAYER_NUMBER_RED = 2;
    final int PLAYER_NUMBER_YELLOW = 3;
    final int PLAYER_NUMBER_GREEN = 4;

    final String BLUE_HEX_COLOR = "#0000FF";
    final String RED_HEX_COLOR = "#FF0000";
    final String YELLOW_HEX_COLOR = "#FFFF00";
    final String GREEN_HEX_COLOR = "#00FF00";

    final int GAME_LOST = 0;
    final int GAME_WON = 1;

    final String GAME_LOST_MESSAGE = "You win!";
    final String GAME_WON_MESSAGE = "You lost!";

    Average m_avg;
    GameClient m_client;
    TextView accelerometerValue;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        accelerometerValue = (TextView) findViewById(R.id.accelerometerValue);

        m_client = GameClient.GetInstance();
        m_client.addServerListener(this);
        m_client.execute();
        m_avg = new Average(m_client);
        Timer timer = new Timer();
        timer.scheduleAtFixedRate(m_avg,0,33L);

        switch (m_client.getPlayerColor())
        {
            case PLAYER_NUMBER_BLUE:
                findViewById(R.id.accelerometerValue).getRootView()
                        .setBackgroundColor(Color.parseColor(BLUE_HEX_COLOR));
                break;
            case PLAYER_NUMBER_RED:
                findViewById(R.id.accelerometerValue).getRootView()
                        .setBackgroundColor(Color.parseColor(RED_HEX_COLOR));
                break;
            case PLAYER_NUMBER_YELLOW:
                findViewById(R.id.accelerometerValue).getRootView()
                        .setBackgroundColor(Color.parseColor(YELLOW_HEX_COLOR));
                break;
            case PLAYER_NUMBER_GREEN:
                findViewById(R.id.accelerometerValue).getRootView()
                        .setBackgroundColor(Color.parseColor(GREEN_HEX_COLOR));
                break;
        }

        m_avg.run();
    }

    @Override
    public void onResume()
    {
        super.onResume();

        //Check device supported Accelerometer sensor or not
        if (SensorMan.isSupported(this))
        {
            //Start Accelerometer Listening
            SensorMan.startListening(m_avg);
        }
    }

    @Override
    public void onStop()
    {
        super.onStop();

        //Check device supported Accelerometer sensor or not
        if (SensorMan.isListening())
        {
            //Start Accelerometer Listening
            SensorMan.stopListening();

        }

    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
        if (SensorMan.isListening())
        {
            SensorMan.stopListening();
        }
        m_client.CloseGameClient();
    }

    @Override
    public void onServerMessageEndGame(int result)
    {
        //Check device supported Accelerometer sensor or not
        if (SensorMan.isListening())
        {
            //Start Accelerometer Listening
            SensorMan.stopListening();
        }
        switch (result)
        {
            case GAME_LOST:
                accelerometerValue.setText(GAME_LOST_MESSAGE);
                break;
            case GAME_WON:
                accelerometerValue.setText(GAME_WON_MESSAGE);
                break;
        }
    }
}