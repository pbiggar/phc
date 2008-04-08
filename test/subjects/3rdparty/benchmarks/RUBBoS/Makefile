
###########################
#    RUBBoS Makefile      #
###########################


##############################
#    Environment variables   #
##############################

JAVA  = /usr/java/jdk1.3.1/bin/java
# JAVAC = /usr/java/jdk1.3.1/bin/javac
JAVAC = /usr/bin/jikes
JAVACOPTS = +E -deprecation
JAVACC = $(JAVAC) $(JAVACOPTS)
RMIC = /usr/java/jdk1.3.1/bin/rmic
RMIREGISTRY= /usr/java/jdk1.3.1/bin/rmiregistry 
CLASSPATH = .:/usr/java/j2sdkee1.3/lib/j2ee.jar:/usr/java/jdk1.3.1/jre/lib/rt.jar:/opt/jakarta-tomcat-3.2.3/lib/servlet.jar
JAVADOC = /usr/java/jdk1.3.1/bin/javadoc


####################
#    EJB version   #
####################

EntityBeans = Category Region User Item OldItem Bid Comment BuyNow
SessionBeans = Query
BeansFiles = $(EntityBeans) $(addsuffix Home,$(EntityBeans)) $(addsuffix PK,$(EntityBeans)) $(addsuffix Bean,$(EntityBeans)) \
	     $(SessionBeans) $(addsuffix Home,$(SessionBeans)) $(addsuffix Bean,$(SessionBeans))

all_beans_sources =  $(addprefix edu/rice/rubbos/beans/, $(addsuffix .java, $(BeansFiles))) edu/rice/rubbos/beans/TimeManagement.java edu/rice/rubbos/beans/ItemAndBids.java
all_beans_obj = $(addprefix edu/rice/rubbos/beans/, $(addsuffix .class, $(BeansFiles))) edu/rice/rubbos/beans/TimeManagement.class edu/rice/rubbos/beans/ItemAndBids.class

beans_xml = $(addprefix META-INF/, $(addsuffix .xml, $(SessionBeans)))  $(addprefix META-INF/, $(addsuffix .xml, $(EntityBeans))) 

beans:  $(all_beans_obj) $(beans_xml) 

%.xml: Makefile
	GenIC -rmiopts -d . -javac $(JAVAC) -javacopts $(JAVACOPTS) -verbose $@

EJB_Servlets = ServletPrinter Config \
	   BrowseCategories BrowseRegions SearchItemsByCategory SearchItemsByRegion \
	   ViewItem ViewUserInfo ViewBidHistory AboutMe \
	   Auth RegisterUser RegisterItem SellItemForm \
	   BuyNow BuyNowAuth StoreBuyNow PutBidAuth PutBid StoreBid PutCommentAuth PutComment StoreComment

all_ejb_servlets_sources =  $(addprefix edu/rice/rubbos/beans/servlets/, $(addsuffix .java, $(EJB_Servlets)))
all_ejb_servlets_obj = $(addprefix edu/rice/rubbos/beans/servlets/, $(addsuffix .class, $(EJB_Servlets)))

ejb_servlets: $(all_ejb_servlets_obj)

clean_ejb_servlets:
	rm -f edu/rice/rubbos/beans/servlets/*.class

#########################
#    Servlets version   #
#########################

Servlets = ServletPrinter Config TimeManagement BrowseCategories Auth RegisterUser RubbosHttpServlet \
	BrowseRegions SearchItemsByCategory SearchItemsByRegion ViewItem ViewBidHistory \
	ViewUserInfo SellItemForm RegisterItem PutCommentAuth PutComment StoreComment \
	BuyNowAuth BuyNow StoreBuyNow PutBidAuth PutBid StoreBid AboutMe \

all_servlets_sources =  $(addprefix edu/rice/rubbos/servlets/, $(addsuffix .java, $(Servlets)))
all_servlets_obj = $(addprefix edu/rice/rubbos/servlets/, $(addsuffix .class, $(Servlets)))

servlets: $(all_servlets_obj)

clean_servlets:
	rm -f edu/rice/rubbos/servlets/*.class

####################
#       Client     #
####################

ClientFiles = URLGenerator URLGeneratorPHP RUBBoSProperties Stats \
	      TransitionTable ClientEmulator UserSession 

all_client_sources =  $(addprefix edu/rice/rubbos/client/, $(addsuffix .java, $(ClientFiles)))
all_client_obj = $(addprefix edu/rice/rubbos/client/, $(addsuffix .class, $(ClientFiles))) edu/rice/rubbos/beans/TimeManagement.class

client: $(all_client_obj)

initDB:
	${JAVA} -classpath .:./database edu.rice.rubbos.client.InitDB ${PARAM}

emulator:
	${JAVA} -classpath . edu.rice.rubbos.client.ClientEmulator


############################
#       Global rules       #
############################


all: beans ejb_servlets client javadoc flush_cache

world: all servlets

javadoc :
	${JAVADOC} -d ./doc/api -bootclasspath ${CLASSPATH} -version -author -windowtitle "RUBBoS API" -header "<b>RUBBoS (C)2001 Rice University/INRIA</b><br>" edu.rice.rubbos.beans edu.rice.rubbos.beans.servlets edu.rice.rubbos.client

clean:
	rm -f core edu/rice/rubbos/beans/*.class edu/rice/rubbos/beans/JOnAS* edu/rice/rubbos/beans/servlets/*.class edu/rice/rubbos/client/*.class edu/rice/rubbos/servlets/*.class

%.class: %.java
	${JAVACC} -classpath ${CLASSPATH} $<

flush_cache: bench/flush_cache.c
	gcc bench/flush_cache.c -o bench/flush_cache