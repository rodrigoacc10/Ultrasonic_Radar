def TAG_VERSION
pipeline {
    agent any
    stages {
        stage('Authentication') {
            steps {
                echo 'Exporting token...'
                sh '''export PLATFORMIO_AUTH_TOKEN=${MX_PLATFORMIO_AUTH_TOKEN}'''
                    /*script {
                        def userInput = input(id: 'myInput', message: 'Please select remote target:', parameters: [
                        [$class: 'ChoiceParameterDefinition', name: 'target', choices: 'MX\nMCH', description: 'Choose the target environment']
                    ])
                    def selectedEnvironment = userInput.target
                    echo "Selected environment: ${selectedEnvironment}"
                    // Further actions based on the selected environment
                        if (selectedEnvironment == 'MX') {
                            echo "Deploying to MX..."
                            sh '''export PLATFORMIO_AUTH_TOKEN=${MX_PLATFORMIO_AUTH_TOKEN}'''
                        } else if (selectedEnvironment == 'MCH') {
                            echo "Deploying to MCH..."
                            sh '''export PLATFORMIO_AUTH_TOKEN=${MX_PLATFORMIO_AUTH_TOKEN}'''
                        } else {
                            echo "Deploying to Other"
                            sh '''export PLATFORMIO_AUTH_TOKEN=${MX_PLATFORMIO_AUTH_TOKEN}'''
                        }
                    }*/
                       
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
                    sh '''export PLATFORMIO_AUTH_TOKEN=${MX_PLATFORMIO_AUTH_TOKEN}'''
                    sh '''pio remote test -e uno_lrv -vvv'''
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
                    sh "git tag ${TAG_VERSION}"
                    echo "Global variable value: ${env.GIT_REPO}"
                        withCredentials([string(credentialsId: 'github_token', variable: 'TOKEN')]) {
                            sh "git remote set-url origin https://${TOKEN}${env.GIT_REPO}"
                            sh '''git push origin --tags'''
                    }
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