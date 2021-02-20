`timescale 1ns / 1ps


module switchToLED(
    input switch,
    output led
    );
    
    assign led = switch;
    
endmodule
