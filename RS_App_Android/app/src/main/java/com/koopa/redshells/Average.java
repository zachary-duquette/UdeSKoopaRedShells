package com.koopa.redshells;

import java.util.TimerTask;

public class Average extends TimerTask implements AccelerometerListener

{
    private final GameClient m_client;
    private float m_currentValue = 0;
    private float m_lastValue = 0;
    private int m_count = 0;

    public Average(GameClient client)
    {
        m_client = client;
    }

    @Override
    public void run()
    {
        if(m_count > 0)
        {
            m_lastValue = m_currentValue / m_count;
            m_client.sendAverage(m_lastValue);
        }
        else
        {
            m_client.sendAverage(m_lastValue);
        }
        m_currentValue = 0;
        m_count = 0;
    }

    @Override
    public void onAccelerationChanged(float y, float timeStamp)
    {
        m_currentValue += y;
        m_count++;
    }
}
