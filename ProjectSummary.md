# Introduction #

This MIDI controller design features 4 velocity sensitive pads as well as 4 one-shot sample buttons and a button for changing the note values of the velocity sensitive pads (i.e. there are 2 note banks). This design is based on the Arduino Mega 2560 Microcontroller. The goal of this project was to create a new tool for real time music creation.

# Parts List #
The parts used in this project are tabulated as follows:

| **Part** | **Cost** | **Source** |
|:---------|:---------|:-----------|
| Arduino Mega | $43.00   | visit [here](http://www.superdroidrobots.com/shop/item.aspx?itemid=1292) |
| 4 Force Sensitive Resistors - Square | $7.95 x 4 | visit [here](https://www.sparkfun.com/products/9376)|
| 2 1kΩ resistor ICs (8 pin) | $0.45 x 2 | Obtained From Lab|
| 330 Ω resistor | ~$0.05   | visit [Visit Here](https://www.sparkfun.com/products/11507) |
| 5 Arcade Style Push Buttons | $0.95 x 5 | visit  [here](https://www.sparkfun.com/products/9179) |
| Female MIDI Jack | $1.95    | visit [here](https://www.sparkfun.com/products/9536) |
| Lots of Wire | $8.99    | visit [here](http://www.radioshack.com/product/index.jsp?productId=2049743) |
| Wooden box | ~$6.00   | Any Hardware Store |
| Mouse Pad (tapping surface) | $4.00    | Any Convenience Store |



# Design #

This controller's design was relatively simple in order to allow MIDI messages to be sent without considerable delay. This was done because, for real-time music creation, lag becomes quite noticeable. This design relies on four force sensitive resistors for velocity sensitive note triggering as well as 5 'arcade' style pushbuttons for note bank toggling (1st buttons) and one-shot sampling (4 remaining buttons).

The MIDI protocol utilized in this project is a serial protocol that relies on a baud rate of 31250 (pulse/sec). The data that is sent on the line always comes in the form of 3 bytes. The first byte indicates the command that is to be executed (note on, note off, aux1, polyphonic key press etc.). The second byte indicates the key value (which in this application corresponds to 'pitch'). The third byte contains data on the velocity of the note that is being depressed (if the command uses this data). For more information on MIDI protocol visit [here](http://www.midi.org/techspecs/midimessages.php).

Figures 1 and 2 display two basic circuits utilized for the voltage sensing over Force Sensitive Resistors and the Push Button Logic High/Low circuits respectively. These types of circuits were used for all 4 FSR pads (pins A0-A3) and for the 5 pushbuttons (Interrupt pins 0-4, on the Mega these are pins 2,3,21,20 and 19).


<a href='http://www.flickr.com/photos/95495101@N03/8726249197/' title='FSR Circuit'><img src='http://farm8.staticflickr.com/7357/8726249197_7d28d311d0.jpg' alt='FSR Circuit' width='500' height='290'><a />


<b>Figure 1:</b> Basic Circuit Utilized for FSR Pad Reading<br>
<br>
This FSR pad schematic originally used analog pin A0 to indicate the level of pad depression in correspondence to a tone frequency. In the final version, which is discussed below, these pads were used to sense an impulse and deliver force information in order to alter note velocity, rather than pitch.<br>
<br>
<a href='http://www.flickr.com/photos/95495101@N03/8726249211/' title='Button Circuit'><img src='http://farm8.staticflickr.com/7398/8726249211_15e440b8dc.jpg' alt='Button Circuit' width='500' height='316'><a />


<b>Figure 2:</b> Basic Circuit Utilized for Pushbutton Triggering<br>
<br>
This is a simple circuit which allows a button to trigger logic high and low (+5V-0V). The pin indicated in this diagram is interrupt pin 0 (pin 2 on the Arduino Mega). In the final version this schematic is duplicated 4 more times to accomodate all 5 push buttons.<br>
<br>
<br>
<a href='http://www.flickr.com/photos/95495101@N03/8726249185/' title='midi jack circuit by halljj2, on Flickr'><img src='http://farm8.staticflickr.com/7448/8726249185_87287ea746.jpg' alt='midi jack circuit' width='500' height='334'><a />

<b>Figure 3:</b> MIDI Jack Connections<br>
<br>
Figure 3 displays the basic lines necessary on a MIDI Jack connection in order to send a single channel MIDI command. Each of these three circuits were implemented in the first build of this device in order to become acclimated with responsiveness of FSRs. Final pin assignments can be viewed in the final code: <a href='https://code.google.com/p/ece-387-midi-drum-controller/source/browse/MIDI_Control_Final.ino'>MIDI_Control_Final</a>.<br>
<br>
<h1>Construction</h1>

Construction of this apparatus took place in two stages. The initial construction of this device had no containing apparatus (i.e. Wooden Box in final version) and utilized a single velocity sensitive pad and a single button in order to experiment with the MIDI Protocol. A depression of the push button would correspond to a note high signal on some MIDI Note (0-127 values) at a medium velocity. The note value mentioned was determined by what the ADC on pin A0 read, that is, pressure on the FSR determined pitch of the note for this implementation.<br>
<br>
Final construction implemented the concepts tested from the initial construction but in a slightly different manner. This version essentially implements multiples of the same circuits outlined in the design section. The was enclosed in a wooden box the was constructed 1" X 4" pine sides and two, top and bottom, masonite panels.<br>
<br>
<h1>Code</h1>

The code for this project and all developmental versions can be found in the 'Source' section of this website.<br>
The version utilized for the initial build is labeled <a href='https://code.google.com/p/ece-387-midi-drum-controller/source/browse/MIDI_Control.ino'>MIDI_Control</a>. The final build saw 3 versions with increasing functionality, the last of these, and the currently utilized code, is labeled <a href='https://code.google.com/p/ece-387-midi-drum-controller/source/browse/MIDI_Control_Final.ino'>MIDI_Control_Final</a>.<br>
<br>
<br>
<h1>Results</h1>

I believe that this project was largely successful. WIth this system I was able to achieve all of the functionality that I desired in one way or another. If I were to change any two things in the way that I approached this design, I would probably choose a microcontroller with a faster processing speed, and I would have obtained high quality buttons (perhaps buttons that were already denounced). The only reason I say that is because on occasion there would be slips in responsiveness to the one-shot sampling buttons.<br>
<br>
This was a very rewarding project and due to the availability of parts (and the fact that I already owned an Arduino Mega), I was able to create a MIDI controller for my music production for only around $40! Typically a drum controller with the same functionality would be upwards of $120.<br>
<br>
The following is a video demonstrating the velocity sensitive pads and one-shot sample triggering from push-buttons:<br>
<br>
<a href='http://www.youtube.com/watch?feature=player_embedded&v=DIpShDn9p5c' target='_blank'><img src='http://img.youtube.com/vi/DIpShDn9p5c/0.jpg' width='425' height=344 /></a>