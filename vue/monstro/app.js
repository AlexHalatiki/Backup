new Vue({
    el: '#app',
    data:{
        start: false,
        perdeu: null,
        danger1: false,
        danger2: false,
        width1: 100,
        width2: 100,
        log: []
    },
    methods:{
        ataque(){
            this.width1 -= 10
            this.width2 -= 8
            this.log.push('MONSTRO ATINGIU JOGADOR COM 10')
            this.log.push('JOGADOR ATINGIU MONSTRO COM 8')
            if(this.width2 < 0)
                this.width2 = 0
            this.verificar()
        },
        ataqueEspecial(){
            this.width1 -= 9
            this.width2 -= 10
            this.log.push('MONSTRO ATINGIU JOGADOR COM 9')
            this.log.push('JOGADOR ATINGIU MONSTRO COM 10')
            if(this.width2 < 0)
            this.width2 = 0
            this.verificar()
        },
        curar(){
            this.width1 += 8
            this.width1 -= 6
            this.log.push('MONSTRO ATINGIU JOGADOR COM 6')
            this.log.push('JOGADOR GANHOU FORCA DE 8')
            if(this.width1 > 100)
                this.width1 = 100
            this.verificar()
        },
        verificar(){
            if(this.width1 <= 20)
                this.danger1 = true
            else
                this.danger1 = false
            if(this.width2 <= 20)
                this.danger2 = true
            if(this.width1 <= 0){
                this.width1 = 0
                this.perdeu = true
                this.start = false
            }
            else if(this.width2 <= 0){
                this.perdeu = false
                this.start = false
            }           
        },
        reset(){
            this.start = true;
            this.width1 = 100;
            this.width2 = 100;
            this.danger1 = false 
            this.danger2 = false
            this.perdeu = null
            this.log = []
        }
    }
})