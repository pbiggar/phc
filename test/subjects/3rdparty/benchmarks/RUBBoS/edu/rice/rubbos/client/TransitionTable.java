package edu.rice.rubbos.client;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.NumberFormatException;
import java.util.StringTokenizer;
import java.util.NoSuchElementException;
import java.util.Random;
import java.util.Stack;

/**
 * This class provides support for transitions between RUBBoS web site pages.
 * A matrix contains probabilities of transition from one state to another.
 * A ReadExcelTextFile() method generates a matrix from an Excel file saved
 * as text with tab separator. The text file must have the following format :
 * <pre>
 * RUBiS Transition Table <tab> Name of transition set
 *
 * "To >>>
 * From vvvv  "[tab]Home[tab]Register[tab]...list of column headers...[tab]About Me
 * Home                     [tab]probability_1_1[tab]probability_2_1[tab]...[tab]probability_25_1[tab]transition_waiting_time
 * Register                 [tab]probability_1_2[tab]probability_2_2[tab]...[tab]probability_25_2[tab]transition_waiting_time
 * RegisterUser             [tab]probability_1_3[tab]probability_2_3[tab]...[tab]probability_25_3[tab]transition_waiting_time
 * Browse                   [tab]probability_1_4[tab]probability_2_4[tab]...[tab]probability_25_4[tab]transition_waiting_time
 * BrowseCategories         [tab]probability_1_5[tab]probability_2_5[tab]...[tab]probability_25_5[tab]transition_waiting_time
 * SearchItemsInCategory    [tab]probability_1_6[tab]probability_2_6[tab]...[tab]probability_25_6[tab]transition_waiting_time
 * BrowseRegions            [tab]probability_1_7[tab]probability_2_7[tab]...[tab]probability_25_7[tab]transition_waiting_time
 * BrowseCategoriesInRegion [tab]probability_1_8[tab]probability_2_8[tab]...[tab]probability_25_8[tab]transition_waiting_time
 * SearchItemsInRegion      [tab]probability_1_9[tab]probability_2_9[tab]...[tab]probability_25_9[tab]transition_waiting_time
 * ViewItem                 [tab]probability_1_10[tab]probability_2_10[tab]...[tab]probability_25_10[tab]transition_waiting_time
 * ViewUserInfo             [tab]probability_1_11[tab]probability_2_11[tab]...[tab]probability_25_11[tab]transition_waiting_time
 * ViewBidHistory           [tab]probability_1_12[tab]probability_2_12[tab]...[tab]probability_25_12[tab]transition_waiting_time
 * BuyNowAuth               [tab]probability_1_13[tab]probability_2_13[tab]...[tab]probability_25_13[tab]transition_waiting_time
 * BuyNow                   [tab]probability_1_14[tab]probability_2_14[tab]...[tab]probability_25_14[tab]transition_waiting_time
 * StoreBuyBow              [tab]probability_1_15[tab]probability_2_15[tab]...[tab]probability_25_15[tab]transition_waiting_time
 * PutBidAuth               [tab]probability_1_16[tab]probability_2_16[tab]...[tab]probability_25_16[tab]transition_waiting_time
 * PutBid                   [tab]probability_1_17[tab]probability_2_17[tab]...[tab]probability_25_17[tab]transition_waiting_time
 * StoreBid                 [tab]probability_1_18[tab]probability_2_18[tab]...[tab]probability_25_18[tab]transition_waiting_time
 * PutCommentAuth           [tab]probability_1_25[tab]probability_2_19[tab]...[tab]probability_25_19[tab]transition_waiting_time
 * PutComment               [tab]probability_1_20[tab]probability_2_20[tab]...[tab]probability_25_20[tab]transition_waiting_time
 * StoreComment             [tab]probability_1_21[tab]probability_2_21[tab]...[tab]probability_25_21[tab]transition_waiting_time
 * Sell                     [tab]probability_1_22[tab]probability_2_22[tab]...[tab]probability_25_22[tab]transition_waiting_time
 * SelectCategoryToSellItem [tab]probability_1_23[tab]probability_2_23[tab]...[tab]probability_25_23[tab]transition_waiting_time
 * SellItemForm             [tab]probability_1_24[tab]probability_2_24[tab]...[tab]probability_25_24[tab]transition_waiting_time
 * RegisterItem             [tab]probability_1_25[tab]probability_2_25[tab]...[tab]probability_25_25[tab]transition_waiting_time
 * Back probability         [tab]probability_1_26[tab]probability_2_26[tab]...[tab]probability_25_26[tab]transition_waiting_time
 * End of Session           [tab]probability_1_27[tab]probability_2_27[tab]...[tab]probability_25_27[tab]transition_waiting_time
 * ...
 *
 * </pre>
 * Everything after the <code>End of Session</code> line is ignored.
 * <code>Initial state</code> is Home page (column 1).
 * <code>probability_x_y</code> determines the probability to go from state x to state y.
 * 
 * There are 2 extra lines compared to colums. These lines are:
 * <code>Back probability:</code> probability to go back to last page (like the back button of the browser)
 * <code>End of session:</code> probability that the user ends the session (leave the web site).
 * </pre>
 *
 * @author <a href="mailto:cecchet@rice.edu">Emmanuel Cecchet</a> and <a href="mailto:julie.marguerite@inrialpes.fr">Julie Marguerite</a>
 * @version 1.0
 */

public class TransitionTable
{
  private int    nbColumns;
  private int    nbRows;
  private float  transitions[][];
  private int    transitionsTime[];
  private String tableName = null;
  private Random rand = new Random();
  private Stack  previousStates = new Stack();
  private int    currentState = 0;
  private Stats  stats;
  private boolean useTPCWThinkTime;
  private static String[] stateNames;
  
  /**
   * Creates a new <code>TransitionTable</code> instance.
   */
  public TransitionTable(int columns, int rows, Stats statistics, boolean UseTPCWThinkTime)
  {
    nbColumns = columns;
    nbRows = rows;
    stats = statistics;
    transitions = new float[nbColumns][nbRows];
    transitionsTime = new int[nbRows];
    useTPCWThinkTime = UseTPCWThinkTime;
  }


  /**
   * Get the name of the transition table as defined in file.
   *
   * @return name of the transition table.
   */
  public String getTableName() 
  {
    return tableName;
  }


  /**
   * Resets the current state to initial state (home page).
   */
  public void resetToInitialState()
  {
    currentState = 0;
    stats.incrementCount(currentState);
  }


  /**
   * Return the current state value (row index). 
   *
   * @return current state value (0 means initial state)
   */
  public int getCurrentState()
  {
    return currentState;
  }


  /**
   * Return the previous state value (row index). 
   *
   * @return previous state value (-1 means no previous state)
   */
  public int getPreviousState()
  {
    if (previousStates.empty())
      return -1;
    else
    {
      Integer state = (Integer)previousStates.peek();
      return state.intValue();
    }
  }


  /**
   * Go back to the previous state and return the value of the new state
   *
   * @return new state value (-1 means no previous state)
   */
  public int backToPreviousState()
  {
    if (previousStates.empty())
      return -1;
    else
    {
      Integer state = (Integer)previousStates.pop();
      currentState = state.intValue();
      return currentState;
    }
  }


  /**
   * Returns true if the 'End of Session' state has been reached
   *
   * @return true if current state is 'End of Session'
   */
  public boolean isEndOfSession()
  {
    return currentState == (nbRows-1);
  }
  

  /**
   * Return the current state name
   *
   * @return current state name
   */
  public String getCurrentStateName()
  {
    return stateNames[currentState];
  }
  

  /**
   * Return a state name
   *
   * @return current state name
   */
  public static String getStateName(int state)
  {
    return stateNames[state];
  }
  

  /**
   * Compute a next state from current state according to transition matrix.
   *
   * @return value of the next state
   */
  public int nextState()
  {
    int   beforeStep = currentState;
    float step = rand.nextFloat();
    float cumul = 0;
    int   i;

    for (i = 0 ; i < nbRows ; i++)
    {
      cumul = cumul + transitions[currentState][i];
      if (step < cumul)
      {
        currentState = i;
        break;
      }
    }
    // Deal with Back to previous state
    if (currentState == nbRows-2)
    { 
      if (previousStates.empty())
        System.out.println("Error detected: Trying to go back but no previous state is available (currentState:"+currentState+", beforeStep:"+beforeStep);
      else
      { // Back adds both stats of back and new state but only sleep "back waiting time"
        // and return the new state (after back).
        stats.incrementCount(currentState); // Add back state stat
        try
        {
          if (useTPCWThinkTime)
            Thread.currentThread().sleep(TPCWthinkTime());
          else
            Thread.currentThread().sleep((long)((float)transitionsTime[currentState]*ClientEmulator.getSlowDownFactor()));
        }
        catch (java.lang.InterruptedException ie)
        {
          System.err.println("Thread "+Thread.currentThread().getName()+" has been interrupted.");
        }
        Integer previous = (Integer)previousStates.pop();
        currentState = previous.intValue();
        // System.out.println("Thread "+Thread.currentThread().getName()+": Going back from "+stateNames[beforeStep]+" to "+stateNames[currentState]+"<br>\n");
//        stats.incrementCount(currentState); // Add new state stat
        return currentState;
      }
    }
    else
    { // Add this state to history (previousStates) if needed
      if (!isEndOfSession())
      { // If there is no probability to go back from this state, just empty the stack
        if (transitions[currentState][nbRows-2] == 0)
          previousStates.removeAllElements();
        else // else add the previous state to the history just in case we go back !
          previousStates.push(new Integer(beforeStep));
        // System.out.println("Thread "+Thread.currentThread().getName()+": "+stateNames[beforeStep]+" -> "+stateNames[currentState]+"<br>\n");
      }
    }
    stats.incrementCount(currentState);
    try
    {
      if (useTPCWThinkTime)
        Thread.currentThread().sleep(TPCWthinkTime());
      else
        Thread.currentThread().sleep((long)((float)transitionsTime[currentState]*ClientEmulator.getSlowDownFactor()));
    }
    catch (java.lang.InterruptedException ie)
    {
      System.err.println("Thread "+Thread.currentThread().getName()+" has been interrupted.");
    }
    return currentState;
  }

  
  /**
   * Read the matrix transition from a file conforming to the
   * format described in the class description.
   *
   * @param filename name of the file to read the matrix from
   * @return true upon success else false
   */
  public boolean ReadExcelTextFile(String filename)
  { 
    BufferedReader reader;
    int            i = 0;
    int            j = 0;

    // Try to open the file
    try
    {
      reader = new BufferedReader(new FileReader(filename));
    }
    catch (FileNotFoundException f)
    {
      System.err.println("File "+filename+" not found.");
      return false;
    }

    // Now read the file using tab (\t) as field delimiter
    try
    {
      // Header
      StringTokenizer st = new StringTokenizer(reader.readLine(), "\t");
      String s = st.nextToken(); // Should be 'RUBBoS Transition Table'
      tableName = st.nextToken();
//      System.out.println("Reading "+tableName+" from "+filename);
      reader.readLine(); // Empty line
      reader.readLine(); // To >>>
      reader.readLine(); // Column headers

      stateNames = new String[nbRows];
      // Read the matrix
      for (i = 0 ; i < nbRows ; i++)
      {
        st = new StringTokenizer(reader.readLine(), "\t");
        stateNames[i] = st.nextToken();
        for (j = 0 ; j < nbColumns ; j++)
        {
          Float f = new Float(st.nextToken());
          transitions[j][i] = f.floatValue();
        }
        // Last column is transition_waiting_time
        Integer t = new Integer(st.nextToken());
        transitionsTime[i] = 1; // TBF: t.intValue(); 
      }
      reader.close();
    }
    catch (IOException ioe)
    {
      System.err.println("An error occured while reading "+filename+". ("+ioe.getMessage()+")");
      return false;
    }
    catch (NoSuchElementException nsu)
    {
      System.err.println("File format error in file "+filename+" when reading line "+i+", column "+j+". ("+nsu.getMessage()+")");
      return false;
    }
    catch (NumberFormatException ne)
    {
      System.err.println("Number format error in file "+filename+" when reading line "+i+", column "+j+". ("+ne.getMessage()+")");
      return false;
    }
//    System.out.println("Transition matrix successfully build.");
    return true;
  }


  /**
   * Display the transition matrix on the standard output.
   *
   * @param title transition table name to be displayed in title
   */
  protected void displayMatrix(String title)
  {
    int i,j;

    System.out.println("\n<h3><br>### "+title+" Transition table ###</h3>\n");
    System.out.println("Transition set: '"+tableName+"'<br>\n");
    System.out.println("<TABLE border=\"1\" summary=\"transition table\"><TBODY>\n");
    System.out.println("<THEAD><TR><TH>State name");
    for (j = 0 ; j < nbColumns ; j++)
      System.out.print("<TH>"+stateNames[j]);
    System.out.print("<TH>Transition time");
    for (i = 0 ; i < nbRows ; i++)
    {
      System.out.print("\n<TR><TD><div align=left><B>"+stateNames[i]+"</B></div>");
      for (j = 0 ; j < nbColumns ; j++)
        System.out.print("<TD><div align=right>"+Float.toString(transitions[j][i])+"</div>");
      System.out.print("<TD><div align=right>"+Float.toString(transitionsTime[i])+"</div>");
    }
    System.out.println("\n</TBODY></TABLE>\n");
    System.out.println();
  }

  // Negative exponential distribution used by
  //  TPC-W spec for Think Time (Clause 5.3.2.1) and USMD (Clause 6.1.9.2)
  private long TPCWthinkTime()
  {
    double r = rand.nextDouble();
    if (r < (double)4.54e-5)
      return ((long) (r+0.5));
    return  ((long) ((((double)-7000.0)*Math.log(r))+0.5));
  }

}
