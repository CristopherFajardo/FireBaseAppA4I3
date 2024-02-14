import { Component } from '@angular/core';
import { Firestore } from '@angular/fire/firestore';
import { doc, setDoc } from 'firebase/firestore';

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage {
  rutadetabla: any;
  rutadetabla1: any;
  rutadetabla2: any;
  rutadetabla3: any;
  ledstatus: boolean = false;
  ledstatus2: boolean = false;
  ledstatus3: boolean = false;
  ledstatusall: boolean = false;
  

  constructor(private db:Firestore) {
  }
  /*
  async apagar() {
    this.rutadetabla = doc(this.db,'controlLED','LED1');//RUTA DE TABLA EN LA BD
    await setDoc(this.rutadetabla, { encender: false });//CAMBIA EL ATRIBUTO DE LA TABLA
  }
  async encender() {
    this.rutadetabla = doc(this.db,'controlLED','LED1');//RUTA DE TABLA EN LA BD
    await setDoc(this.rutadetabla, { encender: true });//CAMBIA EL ATRIBUTO DE LA TABLA
  }
  */
  async toogleState(){
    this.ledstatus=!this.ledstatus;
    this.rutadetabla=doc(this.db, 'controlLED','LED1')
    await setDoc(this.rutadetabla, { encender: this.ledstatus})
    console.log('Estado de encendido:', this.ledstatus);
  }
  async toogleState2(){
    this.ledstatus2=!this.ledstatus2;
    this.rutadetabla=doc(this.db, 'controlLED','LED2')
    await setDoc(this.rutadetabla, { encender: this.ledstatus2})
    console.log('Estado de encendido:', this.ledstatus2);
  }
  async toogleState3(){
    this.ledstatus3=!this.ledstatus3;
    this.rutadetabla=doc(this.db, 'controlLED','LED3')
    await setDoc(this.rutadetabla, { encender: this.ledstatus3})
    console.log('Estado de encendido:', this.ledstatus3);
  }
  async toogleStateall(){
    this.ledstatusall=!this.ledstatusall;
    this.rutadetabla1=doc(this.db, 'controlLED','LED1')
    this.rutadetabla2=doc(this.db, 'controlLED','LED2')
    this.rutadetabla3=doc(this.db, 'controlLED','LED3')
    await setDoc(this.rutadetabla1, { encender: this.ledstatusall})
    await setDoc(this.rutadetabla2, { encender: this.ledstatusall})
    await setDoc(this.rutadetabla3, { encender: this.ledstatusall})
    console.log('Estado de encendido:', this.ledstatusall);
  }
}
