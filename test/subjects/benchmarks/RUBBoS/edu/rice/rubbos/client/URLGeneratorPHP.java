package edu.rice.rubbos.client;

/**
 * This class provides the needed URLs to access all features of RUBBoS (PHP version).
 * You must provide the name and port of the Web site running RUBBoS as well
 * as the directories where the scripts and HTML files reside. For example:
 * <pre>
 * URLGenerator rubbosWeb = new URLGeneratorEJB("www.testbed.cs.rice.edu", 80, "/PHP", "/PHP");
 * </pre>
 * @author <a href="mailto:cecchet@rice.edu">Emmanuel Cecchet</a> and <a href="mailto:julie.marguerite@inrialpes.fr">Julie Marguerite</a>
 * @version 1.0
 */

public class URLGeneratorPHP extends URLGenerator
{

  /**
   * Set the name and port of the Web site running RUBBoS as well as the
   * directories where the HTML and PHP scripts reside. Examples:
   * <pre>
   * URLGenerator rubbosWeb = new URLGenerator("www.testbed.cs.rice.edu", 80, "/PHP", "/PHP");
   * </pre>
   *
   * @param host Web site address
   * @param port HTTP server port
   * @param HTMLFilesPath path where HTML files reside
   * @param ScriptFilesPath path to the script files
   */
  public URLGeneratorPHP(String host, int port, String HTMLFilesPath, String ScriptFilesPath)
  {
    super(host, port, HTMLFilesPath, ScriptFilesPath);
  }


  /**
   * Returns the name of the Search script.
   *
   * @return Search script name
   */
  public  String SearchScript()
  {
    return "Search.php";
  }


  /**
   * Returns the name of the Browse Categories script.
   *
   * @return Browse Categories script name
   */
  public  String BrowseCategoriesScript()
  {
    return "BrowseCategories.php";
  }

  /**
   * Returns the name of the Stories of the day script.
   *
   * @return Stories of the day script name
   */
  public  String StoriesOfTheDayScript()
  {
    return "StoriesOfTheDay.php";
  }


  /**
   * Returns the name of the Older stories script.
   *
   * @return Older stories script name
   */
  public  String OlderStoriesScript()
  {
    return "OlderStories.php";
  }

  /**
   * Returns the name of the Submit story script.
   *
   * @return Submit story script name
   */
  public  String SubmitStoryScript()
  {
    return "SubmitStory.php";
  }
  /**
   * Returns the name of the Post Comment script.
   *
   * @return Post Comment script name
   */
  public  String PostCommentScript()
  {
    return "PostComment.php";
  }

  /**
   * Returns the name of the Register User script.
   *
   * @return Register User script name
   */
  public  String RegisterUserScript()
  {
    return "RegisterUser.php";
  }

  /**
   * Returns the name of the Browse stories By Category script.
   *
   * @return Browse stories by category By Category script name
   */
  public  String BrowseStoriesByCategoryScript()
  {
    return "BrowseStoriesByCategory.php";
  }

  /**
   * Returns the name of the Store Comment script.
   *
   * @return Store Store comment script name
   */
  public  String StoreCommentScript()
  {
    return "StoreComment.php";
  }

  /**
   * Returns the name of the Store Story script.
   *
   * @return Store Story script name
   */
  public  String StoreStoryScript()
  {
    return "StoreStory.php";
  }

  /**
   * Returns the name of the View Story script.
   *
   * @return View Story script name
   */
  public  String ViewStoryScript()
  {
    return "ViewStory.php";
  }

  /**
   * Returns the name of the View Comment script.
   *
   * @return View Comment Info script name
   */
  public  String ViewCommentScript()
  {
    return "ViewComment.php";
  }

  /**
   * Returns the name of the Moderate Comment script.
   *
   * @return Moderate Comment script name
   */
  public String ModerateCommentScript()
  {
    return "ModerateComment.php";
  }

  /**
   * Returns the name of the Store Moderate Log script.
   *
   * @return Store Moderate Log script name
   */
  public String StoreModerateLogScript()
  {
    return "StoreModeratorLog.php";
  }

  /**
   * Returns the name of the Author Tasks script.
   *
   * @return Author Tasks script name
   */
  public String AuthorTasksScript()
  {
    return "Author.php";
  }

  /**
   * Returns the name of the Review Stories script.
   *
   * @return Review Stories script name
   */
  public String ReviewStoriesScript()
  {
    return "ReviewStories.php";
  }

  /**
   * Returns the name of the Accept Story script.
   *
   * @return Accept Story script name
   */
  public String AcceptStoryScript()
  {
    return "AcceptStory.php";
  }

  /**
   * Returns the name of the Accept Story script.
   *
   * @return Accept Story script name
   */
  public String RejectStoryScript()
  {
    return "RejectStory.php";
  }

}
