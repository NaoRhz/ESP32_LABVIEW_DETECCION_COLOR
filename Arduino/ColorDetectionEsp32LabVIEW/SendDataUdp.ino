void sendPacketData(const char* buf, uint16_t len, uint16_t chunkLength) {
  uint8_t buffer[chunkLength];
  size_t blen = sizeof(buffer);
  size_t rest = len % blen;

  for (uint8_t i = 0; i < len / blen; ++i) {
    memcpy(buffer, buf + (i * blen), blen);
    udp.beginPacket(udpAddress, udpPort);
    udp.write(buffer, chunkLength);
    udp.endPacket();
  }

  if (rest) {
    memcpy(buffer, buf + (len - rest), rest);
    udp.beginPacket(udpAddress, udpPort);
    udp.write(buffer, rest);
    udp.endPacket();   
  }
}
