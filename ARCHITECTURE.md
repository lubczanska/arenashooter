# STRUKTURA PROGRAMU

Po rozpoczęciu gry funkcja reset stage czyści stare linked listy encji jeśli graliśmy już wcześniej i tworzy puste

Wszystkie elementy gry poza interfejsem to structy Entity, w przejściu gameloop funkcje do* iterują się 
przez linked listę wszystkich encji/pocisków/efektów.

* moduły init* inicjują odpowiednie elementy gry ładują tekstury i dźwięki, są wywoływane na początku programu.
* moduły do* wywoływane przez logic opowiadają za logikę gry
* moduły draw* wywoływane przez draw opowiadają za wyświetlanie sprite'ów

