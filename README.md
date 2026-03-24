Dieses Projekt stellt ein einfaches Tool zur leichten Verwendung von regulären Ausdrücken dar.
Statt eines komplexen regulären Ausdrucks kann man Operationen mit einfachen Ausdrücken kaskadieren. 
Angenommen wird fragen mit "host athene" die IP ab. Die Ausgabe lautet:

athene.fritz.box has address 192.168.99.32
athene.fritz.box has IPv6 address fdde:59c3:ad6c:0:c25e:d9aa:3a01:3ac3
athene.fritz.box has IPv6 address fdde:59c3:ad6c:0:6d9:f5ff:fecd:da6f
athene.fritz.box has IPv6 address 2003:e0:6f24:1500:6d9:f5ff:fecd:da6f
athene.fritz.box has IPv6 address 2003:e0:6f24:1500:373f:cdcb:b4c9:60d6

Um die IPv4-Adresse zu erhalten benutzen wir rem zur Aufbereitung:

host athene | rem -e -l "x:IPv6" "a:address" "m:[0-9\.]+"

und erhalten richtig "192.168.99.32"

Die rem Parameter  haben folgende Bedeutung:
-l zeilenweise auswerten
-e Leerzeilen ignorieren
"x:IPv6"  IPv6 Zeilen ignorieren
"a:address" nach dem Wort address weiter verarbeiten
"m:[0-9\.]+" die IP als Wort aus ziffern und Punkt auswählen
