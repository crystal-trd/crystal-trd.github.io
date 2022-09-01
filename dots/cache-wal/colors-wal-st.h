const char *colorname[] = {

  /* 8 normal colors */
  [0] = "#0c0a0a", /* black   */
  [1] = "#504E4C", /* red     */
  [2] = "#6E675C", /* green   */
  [3] = "#90664B", /* yellow  */
  [4] = "#998B72", /* blue    */
  [5] = "#CBA165", /* magenta */
  [6] = "#4F88AC", /* cyan    */
  [7] = "#c8c5bd", /* white   */

  /* 8 bright colors */
  [8]  = "#8c8984",  /* black   */
  [9]  = "#504E4C",  /* red     */
  [10] = "#6E675C", /* green   */
  [11] = "#90664B", /* yellow  */
  [12] = "#998B72", /* blue    */
  [13] = "#CBA165", /* magenta */
  [14] = "#4F88AC", /* cyan    */
  [15] = "#c8c5bd", /* white   */

  /* special colors */
  [256] = "#0c0a0a", /* background */
  [257] = "#c8c5bd", /* foreground */
  [258] = "#c8c5bd",     /* cursor */
};

/* Default colors (colorname index)
 * foreground, background, cursor */
 unsigned int defaultbg = 0;
 unsigned int defaultfg = 257;
 unsigned int defaultcs = 258;
 unsigned int defaultrcs= 258;
