
//----------------------------------------------------------------------------------------------------
/// Key constants used in the SLIP protocol.
enum
  {
  /// Indicates the end of a packet.
  END = 192, /// \brief The decimal END character (octal 0300).
  /// Indicates byte stuffing.
  ESC = 219,///  \brief The decimal ESC character (octal 0333).
  /// ESC ESC_END means END data byte.
  ESC_END = 220, /// \brief The decimal ESC_END character (octal 0334).
  /// ESC ESC_ESC means ESC data byte.
  ESC_ESC = 221  /// \brief The decimal ESC_ESC character (ocatal 0335).
  };
//----------------------------------------------------------------------------------------------------
uint32_t encode(const uint8_t* buffer,uint32_t size,uint8_t* encodedBuffer)
 
    {
        if (size == 0)
            return 0;
 
        size_t read_index  = 0;
        size_t write_index = 0;
 
        // Double-ENDed, flush any data that may have accumulated due to line 
        // noise.
 
        encodedBuffer[write_index++] = END;
 
        while (read_index < size)
        {
            if(buffer[read_index] == END)
              {
                encodedBuffer[write_index++] = ESC;
                encodedBuffer[write_index++] = ESC_END;
                read_index++;
              }
            else if(buffer[read_index] == ESC)
              {
                encodedBuffer[write_index++] = ESC;
                encodedBuffer[write_index++] = ESC_ESC;
                read_index++;
              }
            else
              { 
                encodedBuffer[write_index++] = buffer[read_index++];
              }
        }
        return write_index;
}
//----------------------------------------------------------------------------------------------------
