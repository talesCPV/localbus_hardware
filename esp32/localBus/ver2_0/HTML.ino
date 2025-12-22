const char indexHTML[] PROGMEM = R"-**-(
  <!DOCTYPE html>
  <html>
  <head>
      <title></title>
      <meta http-equiv="refresh" content="0; url=/config">
  </head>
  <body>
      <a href="/config">Login</a>
  </body>
  </html>
)-**-";

const char login[] PROGMEM = R"-**-(
  <!DOCTYPE html>
  <html lang="en">
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>LocalBus 1.0</title>
      <style>

        body{
            font-family: Arial, Helvetica, sans-serif;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            height: 98vh;
            background-color: #c8d0d7;
        }

        label{
            width: 60px;
            display: inline-block;
        }

        input, button{
            padding: 5px;
        }

        button{
            width: 100px;
            margin-top: 20px;
            cursor: pointer;
        }

        hr{
            width: 90%;
            color: #c8d0d7;
        }

        p{
            text-align: center;
            font-size: .8em;
        }

        .form{
            display: flex;
            width: 300px;
            padding-top: 20px;
            background-color: #e7eeec;
            border-radius: 10px;
            flex-direction: column;
            gap: 10px;
            align-items: center;
        }

        .entrada{
            display: flex;
            flex-direction: column;
            gap: 10px;
            justify-content: center;
            align-items: center;
            height: 200px;
        }        

        .bottom{
            width: 100%;
            display: flex;
            flex-direction: column;
        }

      </style>
  </head>
  <body>
      
      <div class="main-screen">
        <div class="form">
            <h2>Login</h2>

            <div class="entrada">
                <p>Digite a senha do usuário de configuração:</p>
                <div>
                    <label for="edtPass">Senha</label>
                    <input type="password" id="edtPass">    
                </div>
        
                <button id="btnLogin">Login</button>
            </div>
            <div class="bottom">
                <hr>
                <p>LocalBus - ver 1.0 | 2026</p>    
            </div>
        </div>
      </div>

  </body>
  <script>

  async function openHTML(template=''){

    if(template.trim() != ""){     

        const temp = document.createElement('div');
        temp.innerHTML = template;
        document.querySelector('body').innerHTML = temp.getElementsByTagName('template')[0].innerHTML
        eval(temp.getElementsByTagName('script')[0].innerHTML);

    }
  }

  function login(usr,pass){
          const param = new URLSearchParams();
            param.append('pass',document.querySelector('#edtPass').value);
                    
            fetch('/openlogin', {
                method: 'POST',
                body: param,
            })
              .then(response => {
                return response.text(); 
              })
              .then(textData => {
                openHTML(textData)
              })
        }

      document.querySelector('#btnLogin').addEventListener('click',()=>{
          login()
      })


  </script>
  </html>
)-**-";

const char menu[] PROGMEM = R"-**-(
    <template>
        <style>
            .bar{
                position: fixed;
                top: 0;
                width: 100%;
                background-color: black;
                color: white;
                display: flex;
                flex-direction: row;
                gap: 20px;
                justify-content: center;
                align-items: center;
            }

            .tab-item{
                font-family: Arial, Helvetica, sans-serif;
                padding: 5px;
                font-weight: bold;
                cursor: pointer;
            }

            .tab{
                display: flex;
                flex-direction: column;
                align-items: center;
                gap: 20px;
                margin-top: 80px;
            }
            fieldset{
                border-radius: 10px;
                width: 100%;
            }
            .screen{
                display: flex;
                flex-direction: column;
                gap: 15px;
                justify-content: center;
                align-items: center;
                padding: 20px;
            }
            .inline{
                display: flex;
                gap: 20px;
                align-items: center;
            }
            .line{
                display: flex;
                flex-direction: row;
                gap: 10px;
            }
            .line input{
                width: 30px;
                text-align: center;
            }

            .inline label{
                min-width: 100px;
                display: inline-block;
                text-align: end;
            }
            .btn{
                padding: 5px;
                border-radius: 6px;
                cursor: pointer;
                font-size: 1em;
                margin-top : unset !important;
            }

            .tiny-btn{
                max-width: 30px;
            }

        </style>

        <div class="bar">
            <div class="tab-item" id="veiculo">Veículo</div>
            <div class="tab-item" id="rede">Rede</div>
            <div class="tab-item" id="config">Configuração</div>
        </div>

        <div class="tab"></div>

    </template>
    <script>
        var main_data = ''
        var tabs = document.querySelectorAll('.tab-item')
        for(let i=0; i<tabs.length; i++){
            tabs[i].addEventListener('click',()=>{
                getHTML(tabs[i].id)
            })
        }
        getHTML(tabs[0].id)

        async function openTab(template=''){

            if(template.trim() != ""){     
                const temp = document.createElement('div');
                temp.innerHTML = template;
                document.querySelector('.tab').innerHTML = temp.getElementsByTagName('template')[0].innerHTML
                eval(temp.getElementsByTagName('script')[0].innerHTML);
            }
        }

        function clearURL(ent){
            return ent[ent.length-1]== "/" ? ent.substr(0,ent.length-1) : ent
        }


        function getHTML(file){
            const param = new URLSearchParams();
            param.append('tab',file);
                    
            fetch('/opentab', {
                method: 'POST',
                body: param,
            })
            .then(response => {
                return response.text(); 
            })
            .then(textData => {
                openTab(textData)
            })
        }

        function saveConfig(param,mess=1){
            fetch('/saveconfig', {
                method: 'POST',
                body: param,
            })
            .then(response => {
                return response.text(); 
            })
            .then(textData => {     
                const json = JSON.parse(textData)
                if(json.save){
                   mess ? alert('Dados salvo com sucesso!') : null
                }
            })
        }

    </script>
)-**-";

const char veiculo[] PROGMEM = R"-**-(
    <template>
        <style>
            fieldset{
                padding: 20px;
                display: flex;
                justify-content: center;
            }
            .ball{
                width: 15px;
                height: 15px;
                border-radius: 50%;
            }
            .off{
                background-color: red;
            }
            .on{
                background-color: green;
            }

            #edtMac{
              text-align: center;
              color: white;
              width: 120px;
            }

        </style>
        <fieldset>
            <legend>Internet</legend>
            <div class="inline">
                <div id="bllInternet" class="ball off"></div>
                <div id="lblInternet">OFFLINE</div>
            </div>
        </fieldset>

        <fieldset>
            <legend>Carro</legend>
            <div class="screen">
                <div class="inline">
                    <label for="edtIdCarro">Cód. Carro</label>
                    <input type="number" id="edtIdCarro" min="1" max="999" value="1">
                    <button class="btn" id="btnConnect">Verificar</button>
                </div>
                <div class="inline">
                    <label for="edtPlaca">Placa</label>
                    <input type="text" id="edtPlaca" maxlength="7">
                </div>
                <div class="inline">
                    <div id="bllConnect" class="ball off"></div>
                    <div id="lblConnect">OFFLINE</div>
                </div>
                <div class="inline">
                    <label for="edtVeic">Veículo</label>
                    <input type="text" id="edtVeic" readonly>
                </div>
                <div class="inline">
                    <label for="edtModelo">Modelo</label>
                    <input type="text" id="edtModelo" readonly>
                </div>
                <div class="inline">
                    <label for="edtGrupo">Grupo</label>
                    <input type="text" id="edtGrupo" readonly>
                </div>
                <div class="inline">
                    <label for="edtMotor">Motorista</label>
                    <input type="text" id="edtMotor" readonly>
                </div>
                <div class="inline">
                    <label for="edtToken">Token</label>
                    <input type="text" id="edtToken" readonly>
                </div>
                <div class="inline">
                    <label for="edtMac">Dispositivo</label>
                    <input type="text" id="edtMac" readonly>
                    <button class="btn tiny-btn" id="btnMacAdd" title="Linkar este dispositivo ao veículo">*</button>
                </div>
            </div>
        </fieldset>

    </template>
    <script>

        getSysData()        

        function getSysData(){

            fetch('/getsysdata', {
                method: 'POST',
            })
            .then(response => {
                return response.text(); 
            })
            .then(textData => {
                main_data = JSON.parse(textData)
                document.getElementById('edtIdCarro').value = main_data.id_carro
                document.getElementById('edtPlaca').value = main_data.placa
                document.getElementById('edtToken').value = main_data.token
                connect()
            })
        }

        function connect(){
            const url = clearURL(main_data.url)+'/getToken.php'
            let id_carro = document.querySelector('#edtIdCarro').value.trim()
            const placa = document.querySelector('#edtPlaca').value.trim()

            const param = new URLSearchParams();
                param.append('url',url);
                param.append('params',`id_carro=${id_carro}&placa=${placa}`);

            fetch('/post', {
                method: 'POST',
                body: param,
            })
            .then(response => {
                return response.text(); 
            })
            .then(textData => {
              console.log(textData)
                const json = JSON.parse(textData)
                console.log(json);
                if(json.hasOwnProperty('code')){
                    document.querySelector('#lblInternet').innerHTML = 'ONLINE'
                    document.querySelector('#bllInternet').classList.remove('off')
                    document.querySelector('#bllInternet').classList.add('on')
                    try{
                      if(json.payload.length){
                          document.querySelector('#edtIdCarro').value = json.payload[0].id_frota
                          document.querySelector('#edtPlaca').value = json.payload[0].placa
                          document.querySelector('#edtVeic').value = json.payload[0].veiculo
                          document.querySelector('#edtModelo').value = json.payload[0].modelo
                          document.querySelector('#edtGrupo').value = json.payload[0].grupo
                          document.querySelector('#edtMotor').value = json.payload[0].motorista
                          document.querySelector('#edtToken').value = json.payload[0].token
                          document.querySelector('#edtMac').value = json.payload[0].device == null ? '' : json.payload[0].device
                          document.querySelector('#lblConnect').innerHTML = 'ONLINE'
                          document.querySelector('#bllConnect').classList.remove('off')
                          document.querySelector('#bllConnect').classList.add('on')
                          document.querySelector('#edtMac').classList.remove('on')
                          document.querySelector('#edtMac').classList.remove('off')
                          document.querySelector('#edtMac').classList.add(document.querySelector('#edtMac').value == main_data.mac?'on':'off')
                      }else{
                          document.querySelector('#lblConnect').innerHTML = 'OFFLINE'
                          document.querySelector('#bllConnect').classList.remove('on')
                          document.querySelector('#bllConnect').classList.add('off')
                          document.querySelector('#edtToken').value = '  '
                          document.querySelector('#edtVeic').value = ''
                          document.querySelector('#edtModelo').value = ''
                          document.querySelector('#edtGrupo').value = ''
                          document.querySelector('#edtMotor').value = ''
                          document.querySelector('#edtMac').value = ''
                      } 
                    }catch{
                      console.log(`Request Error: ${json.code}`)
                    }
                    saveCar()
                }else{
                    document.querySelector('#lblInternet').innerHTML = 'OFFLINE'
                    document.querySelector('#bllInternet').classList.remove('on')
                    document.querySelector('#bllInternet').classList.add('off')
                }              
            })
        }

        function saveCar(){
            const param = new URLSearchParams();
                param.append('id_carro',document.querySelector('#edtIdCarro').value.trim());
                param.append('placa',document.querySelector('#edtPlaca').value.trim());
                param.append('token',document.querySelector('#edtToken').value.trim());
            saveConfig(param,0)
        }

        function saveMacAdd(){
            const param = new URLSearchParams();
                param.append('id_carro',document.querySelector('#edtIdCarro').value.trim());

            fetch('/savemac', {
                method: 'POST',
                body: param,
            })
            .then(response => {
                return response.text(); 
            })
            .then(textData => {
                const json = JSON.parse(textData)
                const payload = JSON.parse(json.payload)
                console.log(payload)
                if(payload.save){
                  alert('Agora este dispositivo esta ligado a este veículo no servidor.')
                  document.querySelector('#edtMac').value = main_data.mac
                  document.querySelector('#edtMac').classList.remove('off')
                  document.querySelector('#edtMac').classList.add('on')
                }
            })
        }

        document.querySelector('#edtIdCarro').addEventListener('change',()=>{
            document.querySelector('#edtPlaca').value = ''
        })

        document.querySelector('#btnConnect').addEventListener('click',()=>{
            connect()
        })

        document.querySelector('#btnMacAdd').addEventListener('click',()=>{
          const placa = document.querySelector('#edtPlaca').value.trim()
          if(placa.length){
            if(confirm(`Linkar este dispositivo a placa ${placa}?`)){
              saveMacAdd()
            }
          }else{
            alert('Precisa conectar a um carro válido!')
          }
        })

    </script>
)-**-";

const char rede[] PROGMEM = R"-**-(
    <template>
        <style></style>

        <fieldset>
            <legend>Internet</legend>
            <div class="screen">
                <div class="inline">
                    <label for="edtSSID">Rede(SSID)</label>
                    <input type="text" id="edtSSID" maxlength="15">
                </div>
        
                <div class="inline">
                    <label for="edtPass">Senha</label>
                    <input type="password" id="edtPass" maxlength="15">
                </div>
        
                <div class="inline">
                    <button class="btn" id="btnSave">Salvar</button>
                </div>
        
            </div>
        </fieldset>
        <fieldset>
            <legend>Máscara de Rede</legend>
            <div class="screen">
                <div class="inline">
                    <label>IP</label>
                    <div class="line">
                        <input type="text" id="edtIP1" maxlength="3">
                        <input type="text" id="edtIP2" maxlength="3">
                        <input type="text" id="edtIP3" maxlength="3">
                        <input type="text" id="edtIP4" maxlength="3">
                    </div>
                </div>
                <div class="inline">
                    <label>Getway</label>
                    <div class="line">
                        <input type="text" id="edtGET1" maxlength="3">
                        <input type="text" id="edtGET2" maxlength="3">
                        <input type="text" id="edtGET3" maxlength="3">
                        <input type="text" id="edtGET4" maxlength="3">
                    </div>
                </div>
                <div class="inline">
                    <label>Subnet</label>
                    <div class="line">
                        <input type="text" id="edtSUB1" maxlength="3">
                        <input type="text" id="edtSUB2" maxlength="3">
                        <input type="text" id="edtSUB3" maxlength="3">
                        <input type="text" id="edtSUB4" maxlength="3">
                    </div>
                </div>
                <div class="inline">
                    <label>Primary DNS</label>
                    <div class="line">
                        <input type="text" id="edtDNS11" maxlength="3">
                        <input type="text" id="edtDNS12" maxlength="3">
                        <input type="text" id="edtDNS13" maxlength="3">
                        <input type="text" id="edtDNS14" maxlength="3">
                    </div>
                </div>
                <div class="inline">
                    <label>Secundary DNS</label>
                    <div class="line">
                        <input type="text" id="edtDNS21" maxlength="3">
                        <input type="text" id="edtDNS22" maxlength="3">
                        <input type="text" id="edtDNS23" maxlength="3">
                        <input type="text" id="edtDNS24" maxlength="3">
                    </div>
                </div>
                <div class="inline">
                    <button class="btn" id="btnSaveIP">Salvar</button>
                </div>
        
            </div>
        </fieldset>
    </template>
    <script>
        
        getNetData()
        
        function getNetData(){
                    
            function setIP(field,value){
                const N = value.split('.')
                for(let i=1; i<5; i++){
                    document.getElementById(field+i).value = N[i-1]
                }
            }

            fetch('/getnetdata', {
                method: 'POST'
            })
            .then(response => {
                return response.text(); 
            })
            .then(textData => {
                const json = JSON.parse(textData)
                console.log(json);
                document.getElementById('edtSSID').value = json.ssid
                document.getElementById('edtPass').value = json.pass
                setIP('edtIP',json.ip)
                setIP('edtGET',json.getaway)
                setIP('edtSUB',json.subnet)
                setIP('edtDNS1',json.primaryDNS)
                setIP('edtDNS2',json.secondaryDNS)
            })
        }

        function postData(ssid,pass){
            const param = new URLSearchParams();
            param.append('ssid',ssid);
            param.append('pass',pass);
                    
            fetch('/savessid', {
                method: 'POST',
                body: param,
            })
            .then(response => {
                return response.text(); 
            })
            .then(textData => {
                const json = JSON.parse(textData)
                if(json.save){
                    alert(`Rede ${ssid} salva com sucesso!, por favor, reinicie o dispositivo!`)
                }else{
                    alert('Houve algum problema durante o processo de gravação, por favor entre em contato com um técnico ou resete o dispositivo e tente novamente.')
                }
                console.log(json);
            })
        }

        function postIP(){
            const param = new URLSearchParams();
                param.append('ip',concat('edtIP'));
                param.append('getway',concat('edtGET'));
                param.append('subnet',concat('edtSUB'));
                param.append('dns1',concat('edtDNS1'));
                param.append('dns2',concat('edtDNS2'));

            function concat(id){
                let out = ''
                for(let i=1; i<=4; i++){
                    out+=Number(document.querySelector(`#${id}${i}`).value).toString(16).padStart(2,0)
                }
                return out
            }

            fetch('/saveip', {
                method: 'POST',
                body: param,
            })
            .then(response => {
                return response.text(); 
            })
            .then(textData => {
                console.log(textData);
            })
            }

            document.querySelector('#btnSave').addEventListener('click',()=>{
                const ssid = document.querySelector('#edtSSID').value
                const pass = document.querySelector('#edtPass').value
                if(confirm('Você deseja salvar as configurações de Internet?')){
                postData(ssid,pass)
                }
            })
        
            document.querySelector('#btnSaveIP').addEventListener('click',()=>{
                if(confirm('Você deseja salvar estas configurações de REDE?')){
                postIP()
                }
            })

    </script>
)-**-";

const char config[] PROGMEM = R"-**-(
    <template/>
        <style></style>

        <fieldset>
            <legend>Segurança do Dispositivo</legend>
            <div class="screen">
        
                <div class="inline">
                    <label for="edtPass">Senha</label>
                    <input type="password" id="edtPass" maxlength="15">
                    <button class="btn tiny-btn" id="look1">#?</button>
                </div>

                <div class="inline">
                    <label for="edtRepass">Confirme</label>
                    <input type="password" id="edtRepass" maxlength="15" placeholder="Repita a senha">
                    <button class="btn tiny-btn" id="look2">#?</button>
                </div>

                <div class="inline">
                    <button class="btn" id="btnSave">Salvar</button>
                </div>
        
            </div>
        </fieldset>
        <fieldset>
            <legend>Servidor</legend>
            <div class="screen">
                <div class="inline">
                    <label for="edtUrl">Engine URL</label>
                    <input type="text" id="edtUrl" maxlength="80" placeholder="ex: www.meuservidor.com.br">
                </div>
                <div class="inline">
                    <label for="edtPin">Pin GPS(seg)</label>
                    <input type="number" id="edtPin" placeholder="Tempo em Seg." value="30" min="10" max="999">
                </div>
                <div class="inline">
                    <button class="btn" id="btnSaveServ">Salvar</button>
                </div>
            </div>
        </fieldset>
    </template>
    <script>
        getSysData()        

        function getSysData(){

            fetch('/getsysdata', {
                method: 'POST',
            })
            .then(response => {
                return response.text(); 
            })
            .then(textData => {
                main_data = JSON.parse(textData)
                document.getElementById('edtUrl').value = main_data.url
                document.getElementById('edtPin').value = main_data.pin
            })
        }
        document.querySelector('#look1').addEventListener('click',()=>{
            const edt = document.querySelector('#edtPass')
            edt.type = edt.type == 'password' ? 'text' : 'password'
        })

        document.querySelector('#look2').addEventListener('click',()=>{
            const edt = document.querySelector('#edtRepass')
            edt.type = edt.type == 'password' ? 'text' : 'password'
        })

        function postData(pass){
            const param = new URLSearchParams();
            param.append('dispseg',pass);
                    
            fetch('/saveseg', {
                method: 'POST',
                body: param,
            })
            .then(response => {
                return response.text(); 
            })
            .then(textData => {
                const json = JSON.parse(textData)
                if(json.save){
                    alert(`Nova senha salva com sucesso, por favor, reinicie o dispositivo.`)
                }else{
                    alert('Houve algum problema durante o processo de gravação, por favor entre em contato com um técnico ou resete o dispositivo e tente novamente.')
                }
                console.log(json);
            })
        }

        document.querySelector('#btnSave').addEventListener('click',()=>{
            const pass = document.querySelector('#edtPass')
            const repass = document.querySelector('#edtRepass')
            if(confirm('Tem certeza que deseja salvar esta senha no dispositivo?')){
                if(pass.value.trim()==repass.value.trim()){
                    postData(pass.value.trim())
                }else{
                    alert('As senhas digitadas não conferem, por favor, digite novamente.')
                    repass.value = ''
                    repass.focus()
                }
            }
        })

          document.querySelector('#btnSaveServ').addEventListener('click',()=>{
            const param = new URLSearchParams();
                param.append('url',clearURL(document.querySelector('#edtUrl').value.trim()));
                param.append('pin',document.querySelector('#edtPin').value.trim());
            saveConfig(param,1)
        })

    </script>
)-**-";
