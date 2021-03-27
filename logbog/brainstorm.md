Gruppe: David Jakobsen, Mathias Gredal

Brainstorm:

- 2D rigidbody physics engine

Planlægning(Brugerhistorier og klasser) <-> arbejdsfordeling:



Versionsoversigt:

- Verdensobjekt til at repræsentere scenen og alle komponenter i scenen
- Rendering af dette verdensobjekt
- Serialisering og indlæsning af verdensobjekt
- Brugergrænseflade til simuleringskontrol og gemme/indlæse tests
- Opdatering af objekters position afhængig af hastighed, acceleration og vinkelhastighed
- Detektering af kollision
  - Anvend Separating Axis Theorem, som går ud på at hvis man kan tegne en linje mellem 2 objekter så kollidere de ikke. Denne metode virker ikke på konkave objekter
  - Hvis man kun har firkanter og cirkler, så kan man anvende simplere metoder
- Solver for de krafter der skal laves for at stoppe objekterne fra at flyve igennem hinanden
  - Beregn normalvinklen for kollisionsoverfladen
  - Beregn penetreringsdybden ud fra projektion på normalvektor
  - Beregn impulsen ud fra normalvektor, dybde og restitution(elasticitet, hvor meget af energien går tabt ved kollision)
  - 
- Overvej om man skal lave en kraft baseret solver
- 