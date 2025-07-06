<map>
  <node ID="root" TEXT="Hardware Framework">
    <node TEXT="Chassis Motors" ID="6d7deb5135e89e36c307f1e74415ad6d" STYLE="bubble" POSITION="right">
      <node TEXT="XL6019 boost to 24V for 4 motors" ID="b521436ae2a61a7b1222f382c19d01fa" STYLE="fork"/>
      <node TEXT="Output interface: Positive/Negative terminals" ID="445e06daf59b9fa5317df3999eb1a7cc" STYLE="fork"/>
    </node>
    <node TEXT="Middle Layer Motor (Pump)" ID="100e591cd97c3a4eabf3485239d35f4e" STYLE="bubble" POSITION="right">
      <node TEXT="TPS5430 step down to 12V" ID="6a784940dddcd47385a29ff4af3aac81" STYLE="fork"/>
      <node TEXT="DRV8870 controls water pump" ID="13fca6e73641e9e0fecdadf3c755b30c" STYLE="fork"/>
      <node TEXT="Test point: TPS5430 12V output" ID="f70f914a4d4974cfc32ff4af9b0acbe5" STYLE="fork"/>
      <node TEXT="Output interface: DRV8870 VOUT1 and VOUT2" ID="a2f69f5af1afc52a622c3e4f736f8e96" STYLE="fork"/>
      <node TEXT="Input interface: IN1 IN2 VREF" ID="ad7b8a5798c81fe8878d8ee8559baeb1" STYLE="fork"/>
    </node>
    <node TEXT="Upper Layer Motor (Stepper)" ID="386b0ac483f9d8824c0676254787614d" STYLE="bubble" POSITION="right">
      <node TEXT="XL6019 boost to 24V" ID="a6dc6f343c45db11767f3b1a0aa293c3" STYLE="fork"/>
      <node TEXT="DRV8825 controls stepper motor" ID="ee8301b9227df6c3b4ee02ca00fc88bd" STYLE="fork"/>
      <node TEXT="Test point: XL6019 24V output" ID="c433ca9c004d04b787294822783dee7b" STYLE="fork"/>
      <node TEXT="Output interface: 4-phase stepper" ID="0dce26e7255ab65e28509192345cc633" STYLE="fork"/>
      <node TEXT="Input interface: See datasheet (11 pins total)" ID="d7c72c97ef5002833bbda60c4cd615b8" STYLE="fork"/>
    </node>
    <node TEXT="Base Control Unit" ID="cfb881fac787339a9705f8edd3f72d3d" STYLE="bubble" POSITION="right">
      <node TEXT="Main controller: stm32f407vet6" ID="31e25f33e3e0a5e6afd681213b21dadc" STYLE="fork"/>
      <node TEXT="TPS5430 step down to 3.3V" ID="6f5e1aec5dfe781829a8eccfe326862f" STYLE="fork"/>
      <node TEXT="Test point: 3.3V output" ID="e33d0f7f7ba5cd203d0f7a1ebba8cc87" STYLE="fork"/>
      <node TEXT="Remote control methods" ID="cdf5c361d9a838cb1c8f559fb0df9b72" STYLE="fork">
        <node TEXT="Micro remote" ID="3af5ddeb38e432fea4ee32e9e871380e" STYLE="fork">
          <node TEXT="TPS5430 step down to 5V" ID="2088d9c3c3bca18f30589e7b7e315657" STYLE="fork"/>
          <node TEXT="Test point: 5V output" ID="517facf7094c3962354f572c1107cfb2" STYLE="fork"/>
          <node TEXT="SBUS inversion circuit" ID="6d51268088e1d6e32970849eb743d1ed" STYLE="fork"/>
          <node TEXT="Input interface: 3V3 power, SBUS signal" ID="56e419011b4303603c31aed8bbf50e73" STYLE="fork"/>
          <node TEXT="Output interface: 5V power for receiver, inverted bus signal" ID="a68360993a625897413f5e1f5372afff" STYLE="fork"/>
        </node>
        <node TEXT="WiFi remote..." ID="f68810eb3e0c32f7c3e208d55ad6b313" STYLE="fork"/>
      </node>
      <node TEXT="External Flash" ID="b8359a6c953439ea5ee77cbcd108ac93" STYLE="fork">
        <node TEXT="W25Q16" ID="ce1ace9757d80971687fceb65449b622" STYLE="fork"/>
        <node TEXT="SPI communication" ID="42e3a7318756d680d6315043aa4aa073" STYLE="fork"/>
      </node>
      <node TEXT="3V3/5V level conversion" ID="e8ef5193590b458c2eae2f0e734e526e" STYLE="fork">
        <node TEXT="4x RS0104 (3V3 to 5V) for motor control signals" ID="888124e89ea5836ac247fb41b6f02268" STYLE="fork"/>
        <node TEXT="4x voltage divider circuits (5V→3.3V) for ADC motor speed signals" ID="ef4ab3c53546b38866916eacbfdf28f5" STYLE="fork"/>
        <node TEXT="Input interface: 3V3, 5V, motor speed signals" ID="de9982bd8ab3f2598252e2bcd786be3d" STYLE="fork"/>
        <node TEXT="Output interface: Motor control signals" ID="7eae1f5129b385a0718aa243ed44e31a" STYLE="fork"/>
      </node>
      <node TEXT="Serial interfaces: USART1, UART5, I2C1" ID="ad58e522e29cf84fc92895f6d408119a" STYLE="fork"/>
      <node TEXT="Need to summarize all I/O interfaces" ID="f5d5c3a66bd2b539bfedba5dfa1a9a16" STYLE="fork"/>
      <node TEXT="Revision log" ID="972e5c6cc938d7242db909f45626639c" STYLE="fork">
        <node TEXT="v1.0.1" ID="2bbaa9b8b659e3e11bfb707bb884c99c" STYLE="fork">
          <node TEXT="Split into power board and control board, top layer still copper pour" ID="d7af16b6b0b5d8599e55380257b27cc2" STYLE="fork"/>
        </node>
        <node TEXT="v1.0.2" ID="ab221ff5c16c7b3f67f8670abf55ea9c" STYLE="fork">
          <node TEXT="TPS5430 Vsen not exactly 1.221V (may reach 1.6V); ENA needs floating" ID="623015c09266cedd4348ee666f094fae" STYLE="fork"/>
          <node TEXT="Crystal circuit not working - use 4-pin oscillator, no copper pour on top layer" ID="330706f0095c4b32ba509f545abf01ec" STYLE="fork"/>
          <node TEXT="BLDC3 top silkscreen label error" ID="3ae199c20209865d2f088ce48578ef15" STYLE="fork"/>
          <node TEXT="SWD interface silkscreen on top layer" ID="e56792f3408c79c814db862b21cc6449" STYLE="fork"/>
        </node>
        <node TEXT="v1.0.3" ID="3ac9b20946460a773a68904204af611d" STYLE="fork">
          <node TEXT="RS0104 connected to NC pin by mistake - needs correction" ID="dd77ad60dbf9e31b21a0f0fc9f39cffe" STYLE="fork"/>
          <node TEXT="For FG signal: use ADC with voltage divider to stay under 3.3V" ID="2a5bf5d59b3fd22142ac37cfecac2199" STYLE="fork"/>
          <node TEXT="Remove SN74" ID="8d1dd79b09b67d65eedf9590093c55f9" STYLE="fork"/>
        </node>
        <node TEXT="v1.0.4" ID="b1d2c0c8ee48afe41c12c694ce61171b" STYLE="fork"/>
      </node>
    </node>
    <node TEXT="Power Supply Board" ID="9f8d8bc126b8b6fb82bf69daa652d8b6" STYLE="bubble" POSITION="right">
      <node TEXT="Input interface: XT-60 battery connector" ID="416d7e9f593826036c3926adab05c448" STYLE="fork"/>
      <node TEXT="Output interface: 7 battery voltage outputs" ID="9258b3ea1891010a1092de0f42041b78" STYLE="fork"/>
    </node>
  </node>
</map>