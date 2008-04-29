<?xml version="1.0" encoding="iso-8859-1"?>
<!-- -*- XML -*- -->

<!--
Probar con:
$ sabcmd main.xsl sample.xml '$formato'=html
$ sabcmd main.xsl sample.xml '$formato'=latex
-->


<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:exsl="http://exslt.org/common"
  extension-element-prefixes="exsl">

  <xsl:output method="text" encoding = "iso-8859-1" indent="yes"/>

  <!-- parámetros -->
  <xsl:param name="formato"/>
  <xsl:strip-space elements="*"/>

  <xsl:template match="page">
    <xsl:choose>
      <xsl:when test="$formato='html'">
	<xsl:apply-templates mode="html"/>
      </xsl:when>
      <xsl:otherwise>
	<xsl:apply-templates mode="latex"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="note" mode="latex">
    nota latex:
    <xsl:apply-templates mode="latex"/>
  </xsl:template>

  <xsl:template match="note" mode="html">
    nota html:
    <xsl:apply-templates mode="html"/>
  </xsl:template>


  <xsl:template match="b" mode="latex">
    <xsl:text>\textbf{</xsl:text><xsl:value-of select="."/><xsl:text>}</xsl:text>
  </xsl:template>

  <xsl:template match="b" mode="html">
    [b]<xsl:value-of select="."/>[/b]
  </xsl:template>

</xsl:stylesheet>
