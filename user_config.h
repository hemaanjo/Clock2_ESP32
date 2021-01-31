/* Grid rows
 * 
 * Options
 * -------
 * 10: 10 rows
 * 11: 11 rows
 */
#define GRID_ROWS 10

/* Grid cols
 * 
 * Options
 * ------- 
 * 11: 11 cols
 */
#define GRID_COLS 11

/* Postition of first LED  
 *   
 * Options
 * -------
 * 0: top-left
 * 1: top-right
 * 2: buttom-left
 * 3: buttom-right
 */
#define GRID_FIRST 1

/* Grid language
 *  
 * Options
 * -------
 * 1: de_DE:     german
 * 2: de_DE_alt: german alternative
 * 3: de_clock2:    Biegert & Funk !original!
 */
#define GRID_LANGUAGE de_clock2

/* Position of single minute LEDs
 *  
 * Options
 * -------
 * 0: before
 * 1: after
 */
#define GRID_SINGLE_MINUTES 0

/* Data PIN, where the LED strip is connected to 
beim ESP32: 3. PIN oben rechts / OBEN=Antenne VORNE = NICHT hinten ;-)
*/
#define PIN4DATA 22
/*Stromversorgung in mA -- sollte aus dem Webinterface raus*/
#define AMPERE 12000 
/*bei OTA Ausgabe über SerialBT*/
//#define SerialBT = 1

/* Time Server etc. */
#define NTPSERVER "pool.ntp.org"
#define TIMEZONE "Europe/Berlin"

/* activePlugin 
*
* Options
* -------
* PLUGINNAME as String
* */
#define PLUGIN_NAME "clock2"

#define WLANSID "dama"
#define WLANPWD "8136699728311780"

/* Ambilight 
 * 
 * Options
 * -------
 * 0: inactive
 * 1: seconds
 * 3: permanent
 * */
#define AMBILIGHT 1

#define AMBILIGHT_LED 120
#define AMBILIGHT_STARTIDX 114
#define TYPEWRITER true
#define TYPEWRITER_DELAY 200
