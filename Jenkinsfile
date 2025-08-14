def TAG_VERSION
pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo 'Building...'
                       /*sh '''pio account logout || true 
                       PLATFORMIO_AUTH_TOKEN=${MX_PLATFORMIO_AUTH_TOKEN} pio remote run -r '''*/ 
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
                    /*sh '''pio account logout || true 
                       PLATFORMIO_AUTH_TOKEN=${MX_PLATFORMIO_AUTH_TOKEN} pio remote test --without-uploading''']*/
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
                        var URLTEXT = "https://${TOKEN}${env.GIT_REPO}"
                        echo "URL: ${URLTEXT}"
                        sh "git remote set-url origin ${URLTEXT}"
                        //sh '''git push origin --tags'''
                    }
            }
        }
        stage('Retrieving open agents') {
            steps {
                echo 'Monitoring'
                
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