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

Die Parameter haben folgende Bedeutung (vollständige und ausführliche Erklärung später)

| Option          | Bedeutung                                          |
|-----------------|----------------------------------------------------|
| `-l`            | Zeilenweise auswerten                              |
| `-e`            | Leerzeilen ignorieren                              |

| Filter          | Filter-Funktion                                    | Ergebnis |
|-----------------|----------------------------------------------------|----------|
| `"x:IPv6"`      | Zeilen ignorieren, die „IPv6" enthalten            | "athene.fritz.box has address 192.168.99.32" |
| `"a:address"`   | Nach dem Wort „address" weiterverarbeiten          | " 192.168.99.32" |
| `"m:[0-9\.]+"`  | Regulärer Ausdruck matched IP                      | "192.168.99.32" |


## Optionen und Parameter

| Option  | long Option | Bedeutung                                          |
|---------|-------------|----------------------------------------------------|
| `-f <s>`| `--file=<s>`  | Eingabe-Datei |
|         |             | default:- (Standardeingabe)                       |
| `-d<s>  | `--delimiter=<s>` | Trenzeichen in Ausgabe bei -l (default="\n") |
| `-D<s>  | `--subdelimiter=<s>` | Trennzeichen bei mehreren Ergebnissen in der Zeile |
| `-l`    | `--linewise`            | Zeilenweise auswerten                              |
| `-e`    | `--noempty`       | Leerzeilen bei der Ausgabe ignorieren (default:false) |
| `-n`    | `--newline` | Zeilenvorschub am Ende (default:false) |
| `-v`   | `--verbose` | Ausführliche Meldungen (default:false) |
| `-h`  | `--help` | Hilfe zum Aufruf |
| `-H`  | `--filterhelp` | Hilfe zur Syntax der Filter |

---

# rem – Chaining Regular Expressions Made Easy

This project provides a simple tool for working with regular expressions without complexity.
Instead of writing a single complicated regex, operations can be cascaded using simple expressions.

## Example: Extracting an IPv4 Address from `host` Output

Suppose `host athene` produces the following output:

```
athene.fritz.box has address 192.168.99.32
athene.fritz.box has IPv6 address fdde:59c3:ad6c:0:c25e:d9aa:3a01:3ac3
athene.fritz.box has IPv6 address fdde:59c3:ad6c:0:6d9:f5ff:fecd:da6f
athene.fritz.box has IPv6 address 2003:e0:6f24:1500:6d9:f5ff:fecd:da6f
athene.fritz.box has IPv6 address 2003:e0:6f24:1500:373f:cdcb:b4c9:60d6
```

To extract the IPv4 address, use `rem` to process the output:

```bash
host athene | rem -e -l "x:IPv6" "a:address" "m:[0-9\.]+"
```

Result: `192.168.99.32`

## Parameters

| Option          | Meaning                                            |
|-----------------|----------------------------------------------------|
| `-l`            | Process input line by line                         |
| `-e`            | Ignore empty lines                                 |

| Filter          | Filter Function                                    | Result |
|-----------------|----------------------------------------------------|--------|
| `"x:IPv6"`      | Ignore lines containing "IPv6"                     | "athene.fritz.box has address 192.168.99.32" |
| `"a:address"`   | Continue processing after the word "address"       | " 192.168.99.32" |
| `"m:[0-9\.]+"`  | Select the IP as a token of digits and dots        | "192.168.99.32" |
