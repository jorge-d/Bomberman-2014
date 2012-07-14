#!/bin/env php
<?php
define('EMPTY', '0');
define('PWALL', '1');
define('BWALL', '2');
define('PLAYER', '3');

if ($argc != 3)
  die("Usage: ./gen.php map name.xml\n");

$filename = $argv[1];
$xmlname = $argv[2];

class MapGenerator extends XMLWriter {

  private $file;
  private $xml;
  private $filename;

  public function __construct($filename) {
    $tmp = file($filename);
    $this->filename = $filename;
    unset($tmp[0]);
    unset($tmp[sizeof($tmp)]);
    foreach ($tmp as $line) {
      $line = substr($line, 1, strlen($line) - 3);
      $this->file[] = str_split(trim($line));
    }
    $this->openMemory();
    $this->setIndent(true);
  }

  private function getElems($elem) {
    $elems = array();
    $y = 0;

    foreach ($this->file as $line) {
      $x = 0;
      foreach ($line as $c) {
	if ($c == $elem) {
	  $elems[] = array('x' => $x,
			   'y' => $y);
	}
	$x++;
      }
      $y++;
    }
    return $elems;
  }

  private function writeElems($type, $balise, $s_balise) {
    $elems = $this->getElems($type);

    if (sizeof($elems) == 0)
      return ;
    $this->startElement($balise);
    if ($type == PLAYER)
      $this->writeAttribute('nb', sizeof($elems));
    foreach ($elems as $elem) {
      $this->startElement($s_balise);
      $this->writeAttribute('x', $elem['x']);
      $this->writeAttribute('y', $elem['y']);
      $this->endElement();
    }
    $this->endElement();
  }

  public function genXml() {
    $this->startDocument('1.0','ISO-8859-1');

    $this->startElement('map');
    $this->writeAttribute('x', sizeof($this->file[0]));
    $this->writeAttribute('y', sizeof($this->file));
    $this->writeAttribute('name', $this->filename);
    $this->endElement();

    $this->writeElems(PLAYER, 'players', 'player');
    $this->writeElems(BWALL, 'bwalls', 'bwall');
    $this->writeElems(PWALL, 'pwalls', 'pwall');

    $this->endElement();
    $this->endDocument();
  }

  public function writeFile($xmlfile) {
    file_put_contents($xmlfile, $this->outputMemory());
  }
}


$map = new MapGenerator($filename);
$map->genXml();
$map->writeFile($xmlname);

?>