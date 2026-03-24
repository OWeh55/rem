# rem – Reguläre Ausdrücke einfach kaskadieren

Dieses Projekt stellt ein einfaches Tool zur leichten Verwendung von regulären Ausdrücken dar.
Statt eines komplexen regulären Ausdrucks kann man Operationen mit einfachen Ausdrücken kaskadieren.

## Beispiel: IPv4-Adresse aus `host`-Ausgabe extrahieren

Angenommen, `host athene` liefert folgende Ausgabe:

```
athene.fritz.box has address 192.168.99.32
athene.fritz.box has IPv6 address fdde:59c3:ad6c:0:c25e:d9aa:3a01:3ac3
athene.fritz.box has IPv6 address fdde:59c3:ad6c:0:6d9:f5ff:fecd:da6f
athene.fritz.box has IPv6 address 2003:e0:6f24:1500:6d9:f5ff:fecd:da6f
athene.fritz.box has IPv6 address 2003:e0:6f24:1500:373f:cdcb:b4c9:60d6
```

Um die IPv4-Adresse zu erhalten, wird `rem` zur Aufbereitung verwendet:

```bash
host athene | rem -e -l "x:IPv6" "a:address" "m:[0-9\.]+"
```

Ergebnis: `192.168.99.32`

## Parameter

| Parameter       | Bedeutung                                          |
|-----------------|----------------------------------------------------|
| `-l`            | Zeilenweise auswerten                              |
| `-e`            | Leerzeilen ignorieren                              |
| `"x:IPv6"`      | Zeilen ignorieren, die „IPv6" enthalten            |
| `"a:address"`   | Nach dem Wort „address" weiterverarbeiten          |
| `"m:[0-9\.]+"`  | Die IP als Wort aus Ziffern und Punkt auswählen    |
