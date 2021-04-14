(function(t){function e(e){for(var i,l,r=e[0],s=e[1],c=e[2],d=0,f=[];d<r.length;d++)l=r[d],Object.prototype.hasOwnProperty.call(a,l)&&a[l]&&f.push(a[l][0]),a[l]=0;for(i in s)Object.prototype.hasOwnProperty.call(s,i)&&(t[i]=s[i]);u&&u(e);while(f.length)f.shift()();return o.push.apply(o,c||[]),n()}function n(){for(var t,e=0;e<o.length;e++){for(var n=o[e],i=!0,r=1;r<n.length;r++){var s=n[r];0!==a[s]&&(i=!1)}i&&(o.splice(e--,1),t=l(l.s=n[0]))}return t}var i={},a={app:0},o=[];function l(e){if(i[e])return i[e].exports;var n=i[e]={i:e,l:!1,exports:{}};return t[e].call(n.exports,n,n.exports,l),n.l=!0,n.exports}l.m=t,l.c=i,l.d=function(t,e,n){l.o(t,e)||Object.defineProperty(t,e,{enumerable:!0,get:n})},l.r=function(t){"undefined"!==typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(t,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(t,"__esModule",{value:!0})},l.t=function(t,e){if(1&e&&(t=l(t)),8&e)return t;if(4&e&&"object"===typeof t&&t&&t.__esModule)return t;var n=Object.create(null);if(l.r(n),Object.defineProperty(n,"default",{enumerable:!0,value:t}),2&e&&"string"!=typeof t)for(var i in t)l.d(n,i,function(e){return t[e]}.bind(null,i));return n},l.n=function(t){var e=t&&t.__esModule?function(){return t["default"]}:function(){return t};return l.d(e,"a",e),e},l.o=function(t,e){return Object.prototype.hasOwnProperty.call(t,e)},l.p="/webusb/";var r=window["webpackJsonp"]=window["webpackJsonp"]||[],s=r.push.bind(r);r.push=e,r=r.slice();for(var c=0;c<r.length;c++)e(r[c]);var u=s;o.push([0,"chunk-vendors"]),n()})({0:function(t,e,n){t.exports=n("56d7")},"56d7":function(t,e,n){"use strict";n.r(e);n("e260"),n("e6cf"),n("cca6"),n("a79d");var i=n("2b0e"),a=function(){var t=this,e=t.$createElement,i=t._self._c||e;return i("v-app",[i("v-app-bar",{staticClass:"cronologic-app-bar",attrs:{app:""}},[i("div",{staticClass:"d-flex align-center"},[i("v-img",{staticClass:"shrink mt-1",attrs:{alt:"cronologic Logo",contain:"",src:n("5953"),width:"100"}})],1),i("div",{staticClass:"d-flex align-center ml-8"},[i("v-toolbar-title",[t._v("WebUSB")])],1),i("v-spacer"),i("div",{staticClass:"d-flex align-center"},[i("span",{staticClass:"theme--light v-label mr-4 hidden-sm-and-down"},[t._v("Device Connection")]),i("v-switch",{attrs:{"append-icon":"mdi-usb",color:t.deviceState===t.DEVICE_CONNECTING?"warning":"success","hide-details":"",loading:t.deviceState===t.DEVICE_CONNECTING},model:{value:t.deviceToggle,callback:function(e){t.deviceToggle=e},expression:"deviceToggle"}})],1)],1),i("v-main",{staticClass:"mt-4"},[i("v-container",[i("v-row",[i("v-col",{attrs:{cols:"12",sm:"6","offset-sm":"3",md:"4","offset-md":"4"}},[i("ClockConfig",{attrs:{disabled:!t.connected}})],1)],1),i("v-row",t._l(t.channelConfig,(function(e){return i("v-col",{key:e.id,attrs:{cols:"12",sm:"6",md:"4",lg:"3"}},[i("ChannelConfig",{attrs:{id:e.id,color:e.color,disabled:!t.connected}})],1)})),1)],1),i("v-snackbar",{attrs:{timeout:5e3},model:{value:t.connectionFakeNotification,callback:function(e){t.connectionFakeNotification=e},expression:"connectionFakeNotification"}},[i("v-icon",{attrs:{color:"light-blue"}},[t._v("mdi-information")]),t._v(" The “connect” toggle is currently just a mockup. No USB connection is made. ")],1)],1)],1)},o=[],l=function(){var t=this,e=t.$createElement,n=t._self._c||e;return n("v-card",{attrs:{outlined:"",disabled:t.disabled}},[n("v-card-title",{class:t.color+" lighten-4"},[t._v(" Channel "+t._s(t.id)+" ")]),n("v-list",[n("v-list-item",[n("v-list-item-content",[n("v-tooltip",{attrs:{bottom:""},scopedSlots:t._u([{key:"activator",fn:function(e){var i=e.on,a=e.attrs;return[n("v-list-item-title",t._g(t._b({},"v-list-item-title",a,!1),i),[t._v(" Multiplier "),n("v-icon",[t._v("mdi-information")])],1)]}}])},[n("span",[t._v(" Set the number of pulses per clock cycle as a fraction, i.e. "),n("sup",[t._v("numerator")]),t._v("/"),n("sub",[t._v("denominator")])])]),n("v-row",[n("v-col",[n("v-text-field",{staticClass:"no-spinbox",attrs:{label:"Numerator",type:"number",rules:t.num_rules},model:{value:t.num,callback:function(e){t.num=e},expression:"num"}})],1),n("v-col",[n("v-text-field",{staticClass:"no-spinbox",attrs:{label:"Denominator",type:"number",rules:t.denom_rules},model:{value:t.denom,callback:function(e){t.denom=e},expression:"denom"}})],1)],1)],1)],1),n("v-divider"),n("v-list-item",[n("v-list-item-content",[n("v-row",[n("v-col",[n("v-text-field",{staticClass:"no-spinbox",attrs:{label:"Phase",type:"number",suffix:"ns",rules:t.phase_rules},model:{value:t.phase_ns,callback:function(e){t.phase_ns=e},expression:"phase_ns"}})],1),n("v-col",[n("v-text-field",{staticClass:"no-spinbox",attrs:{label:"Pulse width",type:"number",suffix:"ns",rules:t.width_rules},model:{value:t.width_ns,callback:function(e){t.width_ns=e},expression:"width_ns"}})],1)],1)],1)],1)],1)],1)},r=[];n("99af"),n("ac1f"),n("1276"),n("466d"),n("a9e3");function s(t){return function(e){return String(e).length<=t||"".concat(t," digit").concat(1===t?"":"s"," max")}}function c(t){return function(e){return e=String(e).split(".",2),!(2===e.length&&e[1].length>t)||"".concat(t," fractional digits max")}}function u(t){return String(t).match(/^[0-9]+$/)?"0"!==String(t)||"cannot be zero":"only positive integers"}function d(t){return!!String(t).match(/^[0-9.]+$/)||"only positive numbers"}var f={name:"ChannelConfig",data:function(){return{num:this.numerator,denom:this.denominator,phase_ns:this.phase,width_ns:this.width,num_rules:[u,s(2)],denom_rules:[u,s(1)],phase_rules:[d,c(5),function(t){return t=parseFloat(t),1e6*t%250!==0?"only multiples of 250 fs":!(t>1e6)||"max 1 ms"}],width_rules:[d,c(3)]}},props:{color:{type:String,default:"grey"},disabled:{type:Boolean,default:!1},id:{type:Number,required:!0},numerator:{type:Number,default:1},denominator:{type:Number,default:1},phase:{type:Number,default:123.45625},width:{type:Number,default:123.456}}},p=f,v=n("2877"),m=n("6544"),b=n.n(m),h=n("b0af"),g=n("99d9"),C=n("62ad"),_=n("ce7e"),V=n("132d"),y=n("8860"),E=n("da13"),x=n("5d23"),w=n("0fd9"),S=n("8654"),N=n("3a2f"),k=Object(v["a"])(p,l,r,!1,null,null,null),I=k.exports;b()(k,{VCard:h["a"],VCardTitle:g["a"],VCol:C["a"],VDivider:_["a"],VIcon:V["a"],VList:y["a"],VListItem:E["a"],VListItemContent:x["a"],VListItemTitle:x["b"],VRow:w["a"],VTextField:S["a"],VTooltip:N["a"]});var D=function(){var t=this,e=t.$createElement,n=t._self._c||e;return n("v-card",{attrs:{outlined:"",disabled:t.disabled}},[n("v-card-title",{staticClass:"grey lighten-3"},[t._v(" Base clock ")]),n("v-list",[n("v-list-item",[n("v-list-item-content",[n("v-row",[n("v-col",{attrs:{cols:"8"}},[n("v-text-field",{staticClass:"no-spinbox",attrs:{label:"Value",type:"number",rules:t.nanoRules},model:{value:t.nanoVal,callback:function(e){t.nanoVal=e},expression:"nanoVal"}})],1),n("v-col",{attrs:{cols:"4"}},[n("v-select",{attrs:{items:t.clockUnits,label:"Unit"},model:{value:t.unitVal,callback:function(e){t.unitVal=e},expression:"unitVal"}})],1)],1)],1)],1)],1)],1)},T=[],O=["kHz","MHz","ns","µs"],j={name:"ClockConfig",data:function(){return{clockUnits:O,nanoVal:this.nanos,unitVal:this.unit,nanoRules:[function(t){return!String(t).match(/-/)||"no negative numbers"},function(t){return!!String(t).match(/^[0-9.]+$/)||"only digits and decimal point allowed"}]}},props:{disabled:{type:Boolean,default:!1},nanos:{type:Number,default:123456789},unit:{type:String,default:"ns",validator:function(t){return-1!==O.indexOf(t)}}}},L=j,B=n("b974"),P=Object(v["a"])(L,D,T,!1,null,null,null),F=P.exports;b()(P,{VCard:h["a"],VCardTitle:g["a"],VCol:C["a"],VList:y["a"],VListItem:E["a"],VListItemContent:x["a"],VRow:w["a"],VSelect:B["a"],VTextField:S["a"]});var A=0,M=1,$=2,G={name:"App",components:{ChannelConfig:I,ClockConfig:F},data:function(){return{channelConfig:[{id:1,color:"red"},{id:2,color:"orange"},{id:3,color:"yellow"},{id:4,color:"lime"},{id:5,color:"green"},{id:6,color:"teal"},{id:7,color:"blue"},{id:8,color:"purple"}],connectionFakeNotification:!1,deviceState:A}},computed:{connected:function(){return this.deviceState===this.DEVICE_CONNECTED},deviceToggle:{get:function(){return this.deviceState!==this.DEVICE_DISABLED},set:function(t){var e=this;t?this.deviceState==this.DEVICE_DISABLED&&(this.deviceState=this.DEVICE_CONNECTING,this.connectionFakeNotification=!0,setTimeout((function(){e.deviceState===e.DEVICE_CONNECTING&&(e.deviceState=e.DEVICE_CONNECTED)}),1e3)):this.deviceState=this.DEVICE_DISABLED}}},created:function(){this.DEVICE_DISABLED=A,this.DEVICE_CONNECTING=M,this.DEVICE_CONNECTED=$}},R=G,U=(n("5c0b"),n("7496")),z=n("40dc"),H=n("a523"),J=n("adda"),q=n("f6c4"),W=n("2db4"),K=n("2fa4"),Q=n("b73d"),X=n("2a7f"),Y=Object(v["a"])(R,a,o,!1,null,null,null),Z=Y.exports;b()(Y,{VApp:U["a"],VAppBar:z["a"],VCol:C["a"],VContainer:H["a"],VIcon:V["a"],VImg:J["a"],VMain:q["a"],VRow:w["a"],VSnackbar:W["a"],VSpacer:K["a"],VSwitch:Q["a"],VToolbarTitle:X["a"]});var tt=n("f309");i["a"].use(tt["a"]);var et=new tt["a"]({});i["a"].config.productionTip=!1,new i["a"]({vuetify:et,render:function(t){return t(Z)}}).$mount("#app")},5953:function(t,e,n){t.exports=n.p+"img/cronologic_logo_2020.e42c9234.png"},"5c0b":function(t,e,n){"use strict";n("9c0c")},"9c0c":function(t,e,n){}});
//# sourceMappingURL=app.4afe3799.js.map