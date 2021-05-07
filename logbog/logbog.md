#### Logbog 2021-03-24

I dag startede vi op på eksamensprojektet, hvor vi først dannede grupper og derefter påbegyndte en brainsturm, hvor vi konkluderede at en 2d rigidbody physicssimulator var bedst. Da det tog lidt tid at lave brainstormen, nåede vi ikke til planlægningen.

#### Logbog 2021-03-26

I dag fremlagde vi ville arbejde med. Resten af timen blev brugt til vidensindsamling, da fysikmotorere er et komplekst emne. Vi anvendte vidensindsamlingen til at gå i gang med at lave en versionsoversigt, samt lavede vi overvejelser om hvilket omfang denne fysikmotor skal have i forhold til egenskaber, som konvekse polygoner, friktion, led osv.

#### Logbog 2021-04-9

I dag har vi lavet alle klasserne klar til implementering. Vi har også lavet et klassediagram, som vi kan støtte det op af. Filstrukteren er sat op med trelagsstruktur og er klar til at arbejdes på... 

#### Logbog 2021-04-12

I dag har vi diskuteret hvad der er blevet lavet over weekenden, samt hvad vi skal arbejde videre med og hvad vi har brug for hjælp med. Vi har desuden testet det kode, som er blevet skrevet, ved manuelle tests hvor både ydeevne og grænsetilfælde(hvor mange objekter kan programmet håndtere osv.). Der blev fundet grafiske fejl ved mange elementer. 

#### Logbog 2021-04-14

I dag blev der arbejdet med at integrere rotation ind koden, og nu kan objekter roterer men der er problemer med vinkelhastigheden ved friktion, hvilket der skal arbejdes videre med. 

#### Logbog 2021-04-21

I dag blev der ikke arbejdet så meget med koden, ud over at rotationsfunktionaliteten er blevet flyttet over i en anden branch, da koden stadig har problemer. Ud over dette så er flowcharten blevet lavet færdig, dog så er den ret kompleks, og mangler stadig dele såsom museklik, så man kunne overveje om man bør splitte den op. 

#### Logbog 2021-04-23

I dag blev ryddet nogle unødvendige filer og variabler og der blev arbejdet med klassediagrammet. Der blev også kigget tilbage på rotationsfunktionaliteten og der er blevet lavet nogle planer i forhold til hvordan man får det til at virke. Det mistænkes at være friktionen, som får objekterne til at dreje meget hurtigt rundt. Lige nu er friktion blevet implementeret med impulser, hvor man modificere objektets hastighed direkte. Dette gør dog beregningerne mere komplekse, og det kan være svært at holde øje med om man overholder loven om energikonservering, da hvis man sætter friktionen meget højt, så får friktionen objektet til at flyve tilbage. Hvis man i stedet beregner friktion med krafter og drejningsmoment, så burde det blive simplere at beregne og gøre rotationen mere stabil.

#### Logbog 2021-04-26

Fokus i fremlæggelser:

- David Jacobsen: Kollisionsdetektering, GUI(rendering, håndtering af museklik), tilhørende tests(tegnes GUI ens på tværs af platforme, fejl i kollisionsdetektering ved f.eks. høje hastigheder)
- Mathias Gredal: Kinematik, datastruktur, tilhørende tests(ydeevne med mange objekter, vibrere objekter når de bør ligge stille, synker tunge objekter, hvordan håndteres objekter som befinder sig inde i andre objekter)

#### Logbog 2021-28-04

vi fandt ud af windows er præinstalleret med rektangel funkktionailitet. Dette fuckede programmet fuldstændig op og tog en dag at debugge.

#### Logbog 2021-05-03

I dag blev der lavet flere kommentarer og der blev fjernet en rå pointer. Derudover er der blevet diskuteret en implementering af kollision med firkanter og koden kan nu også køre på windows

#### Logbog 2021-05-07

I dag fik vi ikke lavet så meget programmeringsmæssigt, og i stedet blev der fokuseret på synopsisen. Desuden var det også den sidste programmeringstime 😭.

