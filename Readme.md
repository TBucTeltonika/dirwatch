Surasti visus daemon.
ps -lA | awk '$12 == "?" {print $4, $14}'

Nuzudyti procesa:
sudo kill -9 PID

Paleisti su root:
sudo ./dirwatchd

Privalumai:
neuzraso ant virsaus jeigu egzistuojanta jau toks failas.
Parsina ir replacina $USR config faile.
Jeigu nera config failo ji sukuria tas pats ir su log failu.

Trukumai:
Gal signalus reiketu sukurti? Bet nesu tikras ar siuo atveju reikalinga. Jeigu buciau kures new_demonstyle gal biski geriau butu.
Gana daug atminties alokaciju.
Nelabai tvarkingas kodas.
getenv getlogin_r ir getuied mato vartotoja kaip 'ROOT' kas neleidzia gerai pasiimti dabartinio vartojojo vardo. Tam padarytas workaround jeigu kompe daugiau negu vienas vartojojas nezinau pas kuri atsidurs failas, turbut ABC tvarka.


