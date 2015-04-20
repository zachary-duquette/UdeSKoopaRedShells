package com.koopa.redshells;

import android.os.AsyncTask;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;


public class GameClient extends AsyncTask<Void, Void, Void>
{
    private final String AVERAGE_TAG;
    private final String COLOR_TAG;
    private final byte DENIED_TAG;
    private final byte END_TAG;

    private int playerColor;

    private String messageIn;
    private StringBuilder messageOut;


    private DataOutputStream out;
    private DataInputStream in;

    byte[] inByteArray;
    byte[] outByteArray;

    private Socket socket = null;

    private static GameClient instance = new GameClient();

    ServerListener serverListener;

    private GameClient()
    {
        inByteArray = new byte[100];
        outByteArray = new byte[100];
        playerColor = -1;
        messageOut = new StringBuilder();

        AVERAGE_TAG = "A";
        COLOR_TAG = "C";
        DENIED_TAG = (byte) 0x44;
        END_TAG = (byte) 0x45;
    }

    public void addServerListener(ServerListener servListener)
    {
        serverListener = servListener;
    }

    @Override
    protected Void doInBackground(Void... params)
    {
        // Preparation before entering STR part
        // first make connection
        try
        {
            // This is Server'PC
            socket = new Socket("192.168.0.100", 8779);
            out = new DataOutputStream(socket.getOutputStream());
            in = new DataInputStream(socket.getInputStream());

            // Wait to receive player number
            in.read(inByteArray);
            messageIn = new String(inByteArray);

            if (messageIn.startsWith(COLOR_TAG))
            {
                playerColor = Integer.parseInt(messageIn.substring(1, 2));

            } else if (inByteArray[0] == DENIED_TAG)
            {

                CloseGameClient();
                return null;
            }
        } catch (Exception e)
        {
            e.printStackTrace();
            CloseGameClient();
            return null;
        }


        // We now have the color
        // Assuming game is started we can wait for the game to end
        try
        {
            do
            {
                in.read(inByteArray);

            } while (inByteArray[0] != END_TAG);

        } catch (Exception e)
        {
            e.printStackTrace();
            CloseGameClient();
        }
        return null;
    }

    public static GameClient GetInstance()
    {
        return instance;
    }

    public void CloseGameClient()
    {
        if (socket != null)
        {
            try
            {
                socket.close();
            } catch (IOException e)
            {
                e.printStackTrace();
            }
        }
    }

    int getPlayerColor()
    {
        while (playerColor == -1)
        {
            try
            {
                Thread.sleep(500);
            } catch (InterruptedException e)
            {
                e.printStackTrace();
                CloseGameClient();
            }
        }
        return playerColor;
    }

    void sendAverage(float average)
    {
        if (out != null)
        {
            try
            {
                messageOut.setLength(0);
                messageOut.append(AVERAGE_TAG).append(average);
                out.write(String.format("%-100s", messageOut.toString()).getBytes());
            } catch (Exception e)
            {
                e.printStackTrace();
                CloseGameClient();
            }
        }
    }
}