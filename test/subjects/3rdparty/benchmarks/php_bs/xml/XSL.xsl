<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/TR/WD-xsl">

<xsl:template match="/">
<html>
<head>
<title>Stocks</title>
</head>
<body bgcolor="#ffffcc" text="#0000ff">
  <xsl:apply-templates/>
</body>
</html>

</xsl:template>

<xsl:template match="portfolio">
 <table border="2" width="50%">
   <tr>
    <th>Stock Symbol</th>
    <th>Company Name</th>
    <th>Price</th>
   </tr>
   <xsl:for-each select="stock">
     <tr>
       <td>
         <i><xsl:value-of select=

           "symbol"/></i>
       </td>
     <td>
        <xsl:value-of select="name"/>
      </td>
     <td>
        <xsl:value-of select="price"/>
      </td>
      </tr>
    </xsl:for-each>
  </table>
</xsl:template>

</xsl:stylesheet>

