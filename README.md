# rem – Reguläre Ausdrücke einfach verketten

Dieses Tool ermöglicht die unkomplizierte Verarbeitung von regulären Ausdrücken durch Verkettung
einfacher Operationen, statt der Anwendung eines einzelnen, komplexen und schwer lesbaren Ausdrucks.

## Beispiel: IPv4-Adresse aus `host`-Ausgabe extrahieren

Angenommen, `host athene` liefert folgende Ausgabe:
```
athene.fritz.box has address 192.168.99.32
athene.fritz.box has IPv6 address fdde:59c3:ad6c:0:c25e:d9aa:3a01:3ac3
athene.fritz.box has IPv6 address fdde:59c3:ad6c:0:6d9:f5ff:fecd:da6f
athene.fritz.box has IPv6 address 2003:e0:6f24:1500:6d9:f5ff:fecd:da6f
athene.fritz.box has IPv6 address 2003:e0:6f24:1500:373f:cdcb:b4c9:60d6
```

Um die IPv4-Adresse zu extrahieren, wird `rem` wie folgt verwendet:
```bash
host athene | rem -e -l "x:IPv6" "a:address" "m:[0-9\.]+"
```

Ergebnis: `192.168.99.32`

Die Parameter haben folgende Bedeutung (vollständige Erklärung weiter unten):

| Option          | Bedeutung                                          |
|-----------------|----------------------------------------------------|
| `-l`            | Zeilenweise auswerten                              |
| `-e`            | Leerzeilen ignorieren                              |

| Filter          | Filter-Funktion                                    | Ergebnis |
|-----------------|----------------------------------------------------|----------|
| `"x:IPv6"`      | Zeilen ignorieren, die „IPv6" enthalten            | "athene.fritz.box has address 192.168.99.32" |
| `"a:address"`   | Eingabe ab dem Wort „address" weitergeben          | " 192.168.99.32" |
| `"m:[0-9\.]+"`  | Regulärer Ausdruck matched IP                      | "192.168.99.32" |


## Optionen und Parameter

| Option  | Long Option              | Bedeutung                                                    |
|---------|--------------------------|--------------------------------------------------------------|
| `-f <s>`| `--file=<s>`             | Eingabe-Datei (default: `-` = Standardeingabe)               |
| `-d<s>` | `--delimiter=<s>`        | Trennzeichen in der Ausgabe bei `-l` (default: `"\n"`)       |
| `-D<s>` | `--subdelimiter=<s>`     | Trennzeichen bei mehreren Ergebnissen in einer Zeile         |
| `-l`    | `--linewise`             | Zeilenweise auswerten                                        |
| `-e`    | `--noempty`              | Leerzeilen bei der Ausgabe ignorieren (default: false)       |
| `-n`    | `--newline`              | Zeilenumbruch am Ende (default: false)                       |
| `-v`    | `--verbose`              | Ausführliche Meldungen (default: false)                      |
| `-h`    | `--help`                 | Hilfe zur Verwendung                                         |
| `-H`    | `--filterhelp`           | Hilfe zur Filter-Syntax                                      |

## Filter

### Filter mit regulären Ausdrücken
Die Filter arbeiten mit "POSIX Extended Regular Expressions" (<regexp>).
Beim Aufruf auf der Kommandozeile müssen die Filterbeschreibungen oft
in Anführungszeichen gesetzt werden, um als **ein** Parameter übergeben
zu werden. Die einfachen Anführungszeichen verhindern alle Ersetzungen
durch die Shell. 

**`"<regexp>"`** oder **`"m:<regexp>"`**  (match)  
Matchen mit <regexp>. Der gematchte Ausdruck wird zurückgegeben.  
"Aller Anfang ist schwer" -- "m:An[[:alpha::]]+" --> "Anfang"

**`"a:<regexp>"`** (after)  
Text nach dem gematchten Ausdruck wird zurückgegeben.  
"Aller Anfang ist schwer" -- "a:An[[:alpha::]]+" --> " ist schwer"  

**`"b:<regexp>"`** (before)  
Text vor dem gematchten Ausdruck wird zurückgegeben.  
"Aller Anfang ist schwer" -- "b:An[[:alpha::]]+" --> "Aller "  

**`"M:<regexp>"`**  (multiple match)  
Matchen mit <regexp>. Alle Vorkommen werden zurückgegeben.  
"Aller Anfang ist schwer" -- "M:A[[:alpha::]]+" --> "Aller:Anfang"

**`"x:<regexp>"`** (exclude)  
Text, indem <regexp> vorkommt wird gelöscht. Die Anwendung ist meist
nur im zeilenweisen Modus sinnvoll.  
"Aller Anfang ist schwer" -- "x:An[[:alpha::]]+" --> ""  
"Aller Anfang ist schwer" -- "x:E[[:alpha::]]+" --> "Aller Anfang ist schwer"  

### Zeichen-Filter

**`"c:<charset>`**  
Nur die gegebenen Zeichen sind erlaubt und andere werden entfernt.  
"Aller Anfang ist schwer" -- "c:Aaei" --> "AeAaie"  

**`"C:<charset>`**  
Die gegebenen Zeichen sind nicht erlaubt und werden entfernt.  
"Aller Anfang ist schwer" -- "C:Aaei" --> "llr nfng st schwr"  

**`"t:<charset>"`**  (trim)
Die gegebenen Zeichen werden am Anfang und am Ende entfernt.
"Aller Anfang ist schwer" -- "t:Arle" --> "r Anfang ist schw"  

**`"T:<pairs>"`** (translate)
Zeichenersetzung. Die angegebenen Zeiche werden als Paare betrachtet
und das erste Zeichen wird durch das zweite ersetzt.  
"Aller Anfang ist schwer" -- "t:AOao" --> "Oller Onfong ist schwer"  


---

# rem – Chaining Regular Expressions Made Easy

This tool makes it easy to process text with regular expressions by chaining simple operations,
instead of writing a single, hard-to-read expression.

## Example: Extracting an IPv4 Address from `host` Output

Suppose `host athene` produces the following output:
```
athene.fritz.box has address 192.168.99.32
athene.fritz.box has IPv6 address fdde:59c3:ad6c:0:c25e:d9aa:3a01:3ac3
athene.fritz.box has IPv6 address fdde:59c3:ad6c:0:6d9:f5ff:fecd:da6f
athene.fritz.box has IPv6 address 2003:e0:6f24:1500:6d9:f5ff:fecd:da6f
athene.fritz.box has IPv6 address 2003:e0:6f24:1500:373f:cdcb:b4c9:60d6
```

To extract the IPv4 address, use `rem` as follows:
```bash
host athene | rem -e -l "x:IPv6" "a:address" "m:[0-9\.]+"
```

Result: `192.168.99.32`

The parameters have the following meaning (full explanation below):

| Option          | Meaning                                            |
|-----------------|----------------------------------------------------|
| `-l`            | Process input line by line                         |
| `-e`            | Ignore empty lines                                 |

| Filter          | Filter Function                                    | Result |
|-----------------|----------------------------------------------------|--------|
| `"x:IPv6"`      | Ignore lines containing "IPv6"                     | "athene.fritz.box has address 192.168.99.32" |
| `"a:address"`   | Pass input starting after the word "address"       | " 192.168.99.32" |
| `"m:[0-9\.]+"`  | Select the IP as a token of digits and dots        | "192.168.99.32" |


## Options and Parameters

| Option  | Long Option              | Meaning                                                      |
|---------|--------------------------|--------------------------------------------------------------|
| `-f <s>`| `--file=<s>`             | Input file (default: `-` = standard input)                   |
| `-d<s>` | `--delimiter=<s>`        | Delimiter in output when using `-l` (default: `"\n"`)        |
| `-D<s>` | `--subdelimiter=<s>`     | Delimiter between multiple results on one line               |
| `-l`    | `--linewise`             | Process input line by line                                   |
| `-e`    | `--noempty`              | Ignore empty lines in output (default: false)                |
| `-n`    | `--newline`              | Append newline at end (default: false)                       |
| `-v`    | `--verbose`              | Verbose messages (default: false)                            |
| `-h`    | `--help`                 | Help on usage                                                |
| `-H`    | `--filterhelp`           | Help on filter syntax                                        |
