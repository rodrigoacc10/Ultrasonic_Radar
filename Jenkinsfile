def TAG_VERSION
def SELECTED_ENV
pipeline {
    agent any
    stages {
        stage('Authentication') {
            steps {
                echo 'Exporting token...'
                    script {
                        def userInput = input(
                        id: 'myMultiOptionInput',
                        message: 'Please select your desired options:',
                        parameters: [
                            choice(
                                name: 'selectedOptions',
                                choices: """
                                Option A
                                Option B
                                Option C
                                """.stripIndent(),
                                description: 'Choose one or more options'
                            )
                        ]
                    )
                    echo "You selected: ${userInput.selectedOptions}"
                    }
                       
            }
        }
        stage('Build') {
            steps {
                echo 'Building...'
                       sh '''pio run -e uno_lrv -vvv'''
            }
        }
        stage('HW Test') {
            steps {
                echo 'Testing..'
                    //sh '''pio account logout || true PLATFORMIO_AUTH_TOKEN=${MX_PLATFORMIO_AUTH_TOKEN} pio remote test -e uno_lrv -vvv'''
            }
        }
        stage('Tagging qa') {
            when {
                branch 'qa' 
            }
            steps {  
                echo 'Creating Tag'            
                    script {
                        def date = new Date().format("yyyy-MM-dd'T'HHmm") // Format the date as yyyy-MM-ddTHHmm
                        TAG_VERSION = "jenkins-v-${date}"
                        echo "Generated version: ${TAG_VERSION}" 
                    }
                echo 'Tagging branch'    
                    /*sh "git tag ${TAG_VERSION}"
                    echo "Global variable value: ${env.GIT_REPO}"
                        withCredentials([string(credentialsId: 'github_token', variable: 'TOKEN')]) {
                            sh "git remote set-url origin https://${TOKEN}${env.GIT_REPO}"
                            sh '''git push origin --tags'''
                    }*/
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying..'
                /*sh '''pio account logout || true 
                PLATFORMIO_AUTH_TOKEN=${MX_PLATFORMIO_AUTH_TOKEN} pio remote run --environment uno --target upload'''*/
            }
        }
    }
    environment {
    MX_PLATFORMIO_AUTH_TOKEN = credentials('MX_PLATFORMIO_AUTH_TOKEN')
  }
}