#ifndef DHT_H_
#define DHT_H_

#include "Energia.h"
#define DHT_REFRESH_TIMEOUT 2000

class dht
{
public:
    static int8_t readRawData(unsigned char pin, int16_t *temperature, int16_t *humidity, boolean dht22);
    static int8_t readFloatData(unsigned char pin, float *temperature, float *humidity, boolean dht22);
    static float convertTemperature(int16_t temperaure);
    static float convertHumidity(int16_t humidity);
    
    //init pin for data transfer
    static void initPin(unsigned char pin);
};



class DhtBuffered
{
public:
    
    //param pin za DHT22
    DhtBuffered(const unsigned char pin, const boolean dht22 = true);

    ~DhtBuffered();
    
    /*
     updates temperature and humidity values if necessary
     param realReadingWasMade returns true when actual values was read,
     otherwise (when values loaded from buffer) returns false
    
     return true when data loaded from buffer or successful read from hardware,
     false when read from hardware was failed
    */
    boolean update(boolean *realReadingWasMade = NULL);

    /*
     temperature returns temperature in int16 values
     param onlyFromCache when true value will be returned only from buffer
     (cache) when have any data in buffer. When no data in buffer
     avail will try to load actual values
     
     return temperature (from sensor or from buffer when have problems
     with sensor and have data in buffer) or -100 when do not have valid data
    */
    int16_t temperature(const boolean onlyFromCache = false) const;

    /*
     humidity returns humidity in int16 values
     param onlyFromCache when true value will be returned only from buffer
     (cache) when have any data in buffer. When no data in buffer
     avail will try to load actual values
    
     return humidity (from sensor or from buffer when have problems
     with sensor and have data in buffer) or -100 when do not have valid data
    */
    int16_t humidity(const boolean onlyFromCache = false) const;
    
    //clears all variables except port number
    void clear();    

    //returns true when have data in buffers
    boolean haveData() const;
protected:
    //reads data from hardware sensor
    boolean readData(boolean *realReadingWasMade = NULL) const;

private:
    //pin number of sensor
    unsigned char           m_Pin;

    //cached temperature
    mutable int16_t         m_Temperature;

    //cached humidity
    mutable int16_t         m_Humidity;

    //holds milis when last reading (from hardware sensor) wa made
    mutable uint32_t        m_LastMillis;

    //true when have data in cache
    mutable boolean         m_HaveData;

    //true when working with DHT22, false when working with DHT11
    boolean                 m_IsDht22;

    //returns true when need to reload data, otherwise returns false
    boolean needReloadData() const;
};



/*Returns buffered temperature and humidity values from DHT22.
  Actualizes temperature and humidity values every DHT_REFRESH_TIMEOUT ms
 
  Returns values in float data type. This way is more useful but requires more moremory in MCU
*/
class DhtBufferedFloat : protected DhtBuffered
{
public:
    /*
     DhtBufferedFloat constructor
     param pin pin number from DHT22
     param dht22 must be true when working with DHT22 
     */
    DhtBufferedFloat(const unsigned char pin, const boolean dht22 = true);

    ~DhtBufferedFloat();

    /*
     update updates temperature and humidity values if necessary
     param realReadingWasMade returns true when actual values was read,
     otherwise (when values loaded from buffer) returns false
     
     return true when data loaded from buffer or successful read from hardware,
     false when read from hardware was failed
    */
    boolean update(boolean *realReadingWasMade = NULL);

    /*
     temperature returns temperature in float data type
     param onlyFromCache when true value will be returned only from buffer
     (cache) when have any data in buffer. When no data in buffer
     avail will try to load actual values
     
     return temperature (from sensor or from buffer when have problems
     with sensor and have data in buffer) or -100 when do not have valid data
    */
    float temperature(const boolean onlyFromCache = false) const;

    /*
     humidity returns humidity in float values
     param onlyFromCache when true value will be returned only from buffer
     (cache) when have any data in buffer. When no data in buffer
     avail will try to load actual values
     
     return humidity (from sensor or from buffer when have problems
     with sensor and have data in buffer) or -100 when do not have valid data
    */
    float humidity(const boolean onlyFromCache = false) const;

    // returns true when have data in buffers
    boolean haveData() const;
};

#endif

