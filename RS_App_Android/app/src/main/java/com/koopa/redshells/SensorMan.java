package com.koopa.redshells;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

import java.util.List;

public class SensorMan
{
    private static Context m_context = null;
    private static boolean m_isRunning = false;
    private static Boolean m_isSupported;
    private static SensorManager m_manager;
    private static AccelerometerListener m_listener;
    private static Sensor m_sensorACC;
    private static Sensor m_sensorMAG;

    private static SensorEventListener m_sensorEventListener =
            new SensorEventListener()
            {
                float[] mGravity;
                float[] mGeomagnetic;
                float R[] = new float[9];
                float I[] = new float[9];
                float orientation[] = new float[3];

                @Override
                public void onSensorChanged(SensorEvent event)
                {

                    if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER)
                        mGravity = event.values;
                    if (event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD)
                        mGeomagnetic = event.values;
                    if (mGravity != null && mGeomagnetic != null)
                    {
                        boolean success = SensorManager.getRotationMatrix(R, I, mGravity, mGeomagnetic);
                        if (success)
                        {
                            SensorManager.getOrientation(R, orientation);
                            m_listener.onAccelerationChanged(orientation[1] / 3.2f,  System.currentTimeMillis());
                        }
                    }
                }

                @Override
                public void onAccuracyChanged(Sensor sensor, int accuracy)
                {

                }
            };


    public static boolean isListening()
    {
        return m_isRunning;
    }

    public static void startListening(AccelerometerListener accelerometerListener)
    {
        m_manager = (SensorManager) m_context.getSystemService(Context.SENSOR_SERVICE);
        m_sensorACC = m_manager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        m_sensorMAG = m_manager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);


        m_manager.registerListener(m_sensorEventListener, m_sensorACC, SensorManager.SENSOR_DELAY_GAME);
        m_manager.registerListener(m_sensorEventListener, m_sensorMAG, SensorManager.SENSOR_DELAY_GAME);

        m_listener = accelerometerListener;
    }

    public static void stopListening()
    {
        try
        {
            if (m_manager != null && m_sensorEventListener != null)
            {
                m_manager.unregisterListener(m_sensorEventListener);
            }
        } catch (Exception ignored)
        {
        }
    }

    public static boolean isSupported(Context context)
    {
        m_context = context;
        if (m_isSupported == null)
        {
            if (m_context != null)
            {


                m_manager = (SensorManager) m_context.
                        getSystemService(Context.SENSOR_SERVICE);

                List<Sensor> sensors = m_manager.getSensorList(
                        Sensor.TYPE_ACCELEROMETER);

                m_isSupported = sensors.size() > 0;

            } else
            {
                m_isSupported = Boolean.FALSE;
            }
        }
        return m_isSupported;
    }
}
