package edu.rice.rubbos.client;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.RandomAccessFile;
import java.util.ResourceBundle;
import java.util.StringTokenizer;
import java.util.Vector;

/**
 * This program check and get all information for the rubbos.properties file
 * found in the classpath.
 *
 * @author <a href="mailto:cecchet@rice.edu">Emmanuel Cecchet</a> and <a href="mailto:julie.marguerite@inrialpes.fr">Julie Marguerite</a>
 * @version 1.0
 */

public class RUBBoSProperties
{
  private static ResourceBundle configuration = null;
  private URLGenerator          urlGen = null;

  // Information about web server
  private String webSiteName;
  private int    webSitePort;
  private String cjdbcSiteName;
  private String EJBHTMLPath;
  private String EJBScriptPath;
  private String ServletsHTMLPath;
  private String ServletsScriptPath;
  private String PHPHTMLPath;
  private String PHPScriptPath;
  private String useVersion;

  // Information about Workload
  private Vector  remoteClients;
  private String  remoteCommand;
  private int     nbOfClients;
  private String  userTransitionTable;
  private String  authorTransitionTable;
  private int     nbOfColumns;
  private int     nbOfRows;
  private int     maxNbOfTransitions;
  private boolean useTPCWThinkTime;
  private int     nbOfStoriesPerPage;
  private int     upTime;
  private float   upSlowdown;
  private int     sessionTime;
  private int     downTime;
  private float   downSlowdown;
  private int     percentOfAuthors;


  // Policy to generate database information
  private String  dbServerName;
  
  private Integer nbOfAuthors;
  private Integer nbOfUsers;

  private String  storyDictionary;
  private Integer storyMaxLength;
  private Integer oldestStoryYear;
  private Integer oldestStoryMonth;

  private Integer maxCommentsPerStory;
  private Integer commentMaxLength;


  // Monitoring information
  private Integer monitoringDebug;
  private String  monitoringProgram;
  private String  monitoringOptions;
  private Integer monitoringSampling;
  private String  monitoringRsh;
  private String  monitoringScp;
  private String  monitoringGnuPlot;
  
  /**
   * Creates a new <code>RUBBoSProperties</code> instance.
   * If the rubbos.properties file is not found in the classpath,
   * the current thread is killed.
   */
  public RUBBoSProperties()
  {
    // Get and check database.properties
    System.out.println("Looking for rubbos.properties in classpath ("+System.getProperty("java.class.path",".")+")<p>");
    try
    {
      configuration = ResourceBundle.getBundle("rubbos");
    }
    catch (java.util.MissingResourceException e)
    {
      System.err.println("No rubbos.properties file has been found in your classpath.<p>");
      Runtime.getRuntime().exit(1);
    }
  }

  
  /**
   * Returns the value corresponding to a property in the rubbos.properties file.
   *
   * @param property the property name
   * @return a <code>String</code> value
   */
  protected String getProperty(String property)
  {
    String s = configuration.getString(property);
    return s;
  }


  /**
   * Check for all needed fields in rubbos.properties and inialize corresponding values.
   * This function returns the corresponding URLGenerator on success.
   *
   * @return returns null on any error or the URLGenerator corresponding to the configuration if everything was ok.
   */
  public URLGenerator checkPropertiesFileAndGetURLGenerator()
  {
    try
    {
      // # HTTP server information
      System.out.println("\n<h3>### HTTP server information ###</h3>");
      System.out.print("Server name       : ");
      webSiteName  = getProperty("httpd_hostname");
      System.out.println(webSiteName+"<br>");
      System.out.print("Server port       : ");
      Integer foo  = new Integer(getProperty("httpd_port"));
      webSitePort = foo.intValue();
      System.out.println(webSitePort+"<br>");
      System.out.print("CJDBC server name : ");
      cjdbcSiteName  = getProperty("cjdbc_hostname");
      System.out.println(cjdbcSiteName+"<br>");
      System.out.print("EJB HTML files path   : ");
      EJBHTMLPath  = getProperty("ejb_html_path");
      System.out.println(EJBHTMLPath+"<br>");
      System.out.print("EJB Script files path : ");
      EJBScriptPath  = getProperty("ejb_script_path");
      System.out.println(EJBScriptPath+"<br>");
      System.out.print("Servlets HTML files path   : ");
      ServletsHTMLPath  = getProperty("servlets_html_path");
      System.out.println(ServletsHTMLPath+"<br>");
      System.out.print("Servlets Script files path : ");
      ServletsScriptPath  = getProperty("servlets_script_path");
      System.out.println(ServletsScriptPath+"<br>");
      System.out.print("Servlets HTML files path   : ");
      PHPHTMLPath  = getProperty("php_html_path");
      System.out.println(PHPHTMLPath+"<br>");
      System.out.print("PHP Script files path : ");
      PHPScriptPath  = getProperty("php_script_path");
      System.out.println(PHPScriptPath+"<br>");
      
      // # Workload
      System.out.println("\n<h3><br>### Workload ###</h3>");
      System.out.print("Remote client nodes            : ");
      StringTokenizer nodes = new StringTokenizer(getProperty("workload_remote_client_nodes"),",");
      remoteClients = new Vector(nodes.countTokens());
      while (nodes.hasMoreTokens())
        remoteClients.add(nodes.nextToken().trim());
      nbOfClients = remoteClients.size();
      System.out.println(nbOfClients+"<br>");
      System.out.print("Remote client command          : ");
      remoteCommand  = getProperty("workload_remote_client_command");
      System.out.println(remoteCommand+"<br>");
      System.out.print("Number of clients              : ");
      foo = new Integer(getProperty("workload_number_of_clients_per_node"));
      nbOfClients = foo.intValue();
      System.out.println(nbOfClients+"<br>");

      System.out.print("User transition table          : ");
      userTransitionTable = getProperty("workload_user_transition_table");
      System.out.println(userTransitionTable+"<br>");
      System.out.print("Author transition table        : ");
      authorTransitionTable = getProperty("workload_author_transition_table");
      System.out.println(authorTransitionTable+"<br>");
      System.out.print("Number of columns              : ");
      foo = new Integer(getProperty("workload_number_of_columns"));
      nbOfColumns = foo.intValue();
      System.out.println(nbOfColumns+"<br>");
      System.out.print("Number of rows                 : ");
      foo = new Integer(getProperty("workload_number_of_rows"));
      nbOfRows = foo.intValue();
      System.out.println(nbOfRows+"<br>");
      System.out.print("Maximum number of transitions  : ");
      foo = new Integer(getProperty("workload_maximum_number_of_transitions"));
      maxNbOfTransitions = foo.intValue();
      System.out.println(maxNbOfTransitions+"<br>");
      System.out.print("Number of stories per page     : ");
      foo = new Integer(getProperty("workload_number_of_stories_per_page"));
      nbOfStoriesPerPage = foo.intValue();
      System.out.println(nbOfStoriesPerPage+"<br>");
      System.out.print("Think time                     : ");
      useTPCWThinkTime = getProperty("workload_use_tpcw_think_time").compareTo("yes") == 0;
      if (useTPCWThinkTime)
        System.out.println("TPCW compatible with 7s mean<br>");
      else
        System.out.println("Using Transition Matrix think time information<br>");
      System.out.print("Up ramp time in ms             : ");
      foo = new Integer(getProperty("workload_up_ramp_time_in_ms"));
      upTime = foo.intValue();
      System.out.println(upTime+"<br>");
      System.out.print("Up ramp slowdown factor        : ");
      Float floo = new Float(getProperty("workload_up_ramp_slowdown_factor"));
      upSlowdown = floo.intValue();
      System.out.println(upSlowdown+"<br>");
      System.out.print("Session run time in ms         : ");
      foo = new Integer(getProperty("workload_session_run_time_in_ms"));
      sessionTime = foo.intValue();
      System.out.println(sessionTime+"<br>");
      System.out.print("Down ramp time in ms           : ");
      foo = new Integer(getProperty("workload_down_ramp_time_in_ms"));
      downTime = foo.intValue();
      System.out.println(downTime+"<br>");
      System.out.print("Down ramp slowdown factor      : ");
      floo = new Float(getProperty("workload_down_ramp_slowdown_factor"));
      downSlowdown = floo.intValue();
      System.out.println(downSlowdown+"<br>");
      System.out.print("Percentage of authors          : ");
      foo = new Integer(getProperty("workload_percentage_of_author"));
      percentOfAuthors = foo.intValue();
      System.out.println(percentOfAuthors+"<br>");

      // # Database Information
      System.out.println("\n<h3><br>### Database Information ###</h3>");
      System.out.print("Database server                : ");
      dbServerName = getProperty("database_server");
      System.out.println(dbServerName+"<br>");

      // # Users policy
      System.out.println("\n<h3><br>### Users policy ###</h3>");
      System.out.print("Number of authors              : ");
      nbOfAuthors = new Integer(getProperty("database_number_of_authors"));
      System.out.println(nbOfAuthors+"<br>");
      System.out.print("Number of users                : ");
      nbOfUsers = new Integer(getProperty("database_number_of_users"));
      System.out.println(nbOfUsers+"<br>");
      
      
      // # Stories policy
      System.out.println("\n<h3><br>### Stories policy ###</h3>");
      System.out.print("Stories dictionary             : ");
      storyDictionary  = getProperty("database_story_dictionnary");
      System.out.println(storyDictionary+"<br>");
      // Check that the dictionnary file is ok to read
      try
      {
        RandomAccessFile f = new RandomAccessFile(storyDictionary, "r");
        String useless = f.readLine();
        f.close();
      }
      catch (Exception e)
      {
        System.err.println("Unable to read dictionary file '"+storyDictionary+"' (got exception: "+e.getMessage()+")");
        return null;
      }
      System.out.print("Stories maximum lenth          : ");
      storyMaxLength = new Integer(getProperty("database_story_maximum_length"));
      System.out.println(storyMaxLength+"<br>");
      System.out.print("Oldest story year              : ");
      oldestStoryYear = new Integer(getProperty("database_oldest_story_year"));
      System.out.println(oldestStoryYear+"<br>");
      System.out.print("Oldest story month             : ");
      oldestStoryMonth = new Integer(getProperty("database_oldest_story_month"));
      System.out.println(oldestStoryMonth+"<br>");

      // # Comments policy
      System.out.println("\n<h3><br>### Comments policy ###</h3>");
      System.out.print("Comment maximum length         : ");
      commentMaxLength      = new Integer(getProperty("database_comment_max_length"));
      System.out.println(commentMaxLength+"<br>");

      // # Monitoring Information
      System.out.println("\n<h3><br>### Database Information ###</h3>");
      System.out.print("Monitoring debugging level     : ");
      monitoringDebug  = new Integer(getProperty("monitoring_debug_level"));
      System.out.println(monitoringDebug+"<br>");
      System.out.print("Monitoring program             : ");
      monitoringProgram  = getProperty("monitoring_program");
      System.out.println(monitoringProgram+"<br>");
      System.out.print("Monitoring options             : ");
      monitoringOptions  = getProperty("monitoring_options");
      System.out.println(monitoringOptions+"<br>");
      System.out.print("Monitoring sampling in seconds : ");
      monitoringSampling = new Integer(getProperty("monitoring_sampling_in_seconds"));
      System.out.println(monitoringSampling+"<br>");
      System.out.print("Monitoring rsh                 : ");
      monitoringRsh      = getProperty("monitoring_rsh");
      System.out.println(monitoringRsh+"<br>");
      System.out.print("Monitoring scp                 : ");
      monitoringScp      = getProperty("monitoring_scp");
      System.out.println(monitoringScp+"<br>");
      System.out.print("Monitoring Gnuplot Terminal    : ");
      monitoringGnuPlot  = getProperty("monitoring_gnuplot_terminal");
      System.out.println(monitoringGnuPlot+"<br>");

      // Create a new URLGenerator according to the version the user has chosen
      System.out.println("\n");
      useVersion = getProperty("httpd_use_version");
      if (useVersion.compareTo("PHP") == 0)
        urlGen = new URLGeneratorPHP(webSiteName, webSitePort, PHPHTMLPath, PHPScriptPath);
//       else if (useVersion.compareTo("EJB") == 0)
//         urlGen = new URLGeneratorEJB(webSiteName, webSitePort, EJBHTMLPath, EJBScriptPath);
      else if (useVersion.compareTo("Servlets") == 0)
	  urlGen = new URLGeneratorServlets(webSiteName, webSitePort, ServletsHTMLPath, ServletsScriptPath);
      else
      {
        System.err.println("Sorry but '"+useVersion+"' is not supported. Only PHP, EJB and Servlets are accepted.");
        return null;
      }
      System.out.println("Using "+useVersion+" version.<br>");
    }
    catch (Exception e)
    {
      System.err.println("Error while checking database.properties: "+e.getMessage());
      return null;
    }
    return urlGen;
  }


  /**
   * Get the web server name
   *
   * @return web server name
   */
  public String getWebServerName()
  {
    return webSiteName;
  }

  /**
   * Get the CJDBC server name
   *
   * @return CJDBC server name
   */
  public String getCJDBCServerName()
  {
    return cjdbcSiteName;
  }


  /**
   * Get the database server name
   *
   * @return database server name
   */
  public String getDBServerName()
  {
    return dbServerName;
  }


  /**
   * Get the total number ofauthors given in the database_number_of_authors field
   *
   * @return total number of authors
   */
  public int getNbOfAuthors()
  {
    return nbOfAuthors.intValue();
  }


  /**
   * Get the total number of users given in the database_number_of_users field
   *
   * @return total number of users
   */
  public int getNbOfUsers()
  {
    return nbOfUsers.intValue();
  }


  /**
   * Get the percentage of emulated users that should be authors (given in the workload_percentage_of_author field)
   *
   * @return percentage of authors
   */
  public int getPercentageOfAuthors()
  {
    return percentOfAuthors;
  }


  /**
   * Get the dictionary file used to build the stories.
   * This file is a plain text file with one word per line.
   *
   * @return dictionary file used to build the stories
   */
  public String getStoryDictionary()
  {
    return storyDictionary;
  }


  /**
   * Get the maximum story length given in the database_story_maximum_length field
   *
   * @return maximum story length
   */
  public int getStoryMaximumLength()
  {
    return storyMaxLength.intValue();
  }


  /**
   * Get the year of the oldest story given in the database_oldest_story_year field
   *
   * @return year of the oldest story
   */
  public int getOldestStoryYear()
  {
    return oldestStoryYear.intValue();
  }


  /**
   * Get the month of the oldest story given in the database_oldest_story_month field
   *
   * @return month of the oldest story
   */
  public int getOldestStoryMonth()
  {
    return oldestStoryMonth.intValue();
  }


  /**
   * Get the maximum comment length given in the comment_max_length field
   *
   * @return maximum comment length
   */
  public int getCommentMaxLength()
  {
    return commentMaxLength.intValue();
  }


  /**
   * Get the user transition table file name given in the workload_user_transition_table field
   *
   * @return user transition table file name
   */
  public String getUserTransitionTable()
  {
    return userTransitionTable;
  }


  /**
   * Get the author transition table file name given in the workload_author_transition_table field
   *
   * @return user transition table file name
   */
  public String getAuthorTransitionTable()
  {
    return authorTransitionTable;
  }


  /**
   * Get the number of columns in the transition table
   *
   * @return number of columns
   */
  public int getNbOfColumns()
  {
    return nbOfColumns;
  }


  /**
   * Get the number of rows in the transition table
   *
   * @return number of rows
   */
  public int getNbOfRows()
  {
    return nbOfRows;
  }


  /**
   * Returns true if TPC-W compatible think time must be used,
   * false if transition matrix think time has to be used.
   *
   * @return if think time should be TPC-W compatible
   */
  public boolean useTPCWThinkTime()
  {
    return useTPCWThinkTime;
  }


  /**
   * Get the number of stories to display per page (when browsing) given in the number_of_storis_per_page field
   *
   * @return number of stories to display per page
   */
  public int getNbOfStoriesPerPage()
  {
    return nbOfStoriesPerPage;
  }


  /**
   * Get the total number of clients user sessions to launch in parallel
   *
   * @return total number of clients
   */
  public int getNbOfClients()
  {
    return nbOfClients;
  }


  /**
   * Get a vector of remote node names to launch clients on
   *
   * @return vector of remote node names to launch clients on
   */
  public Vector getRemoteClients()
  {
    return remoteClients;
  }


  /**
   * Get a vector of remote node names to launch clients on
   *
   * @return vector of remote node names to launch clients on
   */
  public String getClientsRemoteCommand()
  {
    return remoteCommand;
  }


  /**
   * Get the maximum number of transitions a client may perform
   *
   * @return maximum number of transitions
   */
  public int getMaxNbOfTransitions()
  {
    return maxNbOfTransitions;
  }


  /**
   * Get up ramp time in milliseconds
   *
   * @return up ramp time
   */
  public int getUpRampTime()
  {
    return upTime;
  }


  /**
   * Get up ramp slowdown factor
   *
   * @return up ramp slowdown
   */
  public float getUpRampSlowdown()
  {
    return upSlowdown;
  }


  /**
   * Get session time in milliseconds
   *
   * @return session time
   */
  public int getSessionTime()
  {
    return sessionTime;
  }


  /**
   * Get down ramp time in milliseconds
   *
   * @return down ramp time
   */
  public int getDownRampTime()
  {
    return downTime;
  }


  /**
   * Get down ramp slowdown factor
   *
   * @return down ramp slowdown
   */
  public float getDownRampSlowdown()
  {
    return downSlowdown;
  }


  /**
   * Get the monitoring debug level. Level is defined as follow: <pre>
   * 0 = no debug message
   * 1 = just error messages
   * 2 = error messages+HTML pages
   * 3 = everything!
   * </pre>
   *
   * @return monitoring program full path and name
   */
  public int getMonitoringDebug()
  {
    return monitoringDebug.intValue();
  }


  /**
   * Get the monitoring program full path and name
   *
   * @return monitoring program full path and name
   */
  public String getMonitoringProgram()
  {
    return monitoringProgram;
  }


  /**
   * Get the monitoring program options
   *
   * @return monitoring program options
   */
  public String getMonitoringOptions()
  {
    return monitoringOptions;
  }


  /**
   * Get the interval of time in seconds between 2 sample collection by the monitoring program.
   *
   * @return monitoring program sampling time in seconds
   */
  public Integer getMonitoringSampling()
  {
    return monitoringSampling;
  }


  /**
   * Get the rsh program path that should be used to run the monitoring program remotely
   *
   * @return rsh program path
   */
  public String getMonitoringRsh()
  {
    return monitoringRsh;
  }

  /**
   * Get scp program path that should be used to fetch remote files
   *
   * @return rsh program path
   */
  public String getMonitoringScp()
  {
    return monitoringScp;
  }


  /**
   * Get the terminal to use for gnuplot. Usually it is set to 'gif' or 'jpeg'.
   *
   * @return gnuplot terminal
   */
  public String getGnuPlotTerminal()
  {
    return monitoringGnuPlot;
  }

}
