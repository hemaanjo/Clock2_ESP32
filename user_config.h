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
 * 3: de_DE_clock2:    Biegert & Funk !original!
 */
#define GRID_LANGUAGE de_DE

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

/* Time Server etc. */
#define NTPSERVER "pool.ntp.org"
#define TIMEZONE "Europe/Berlin"
