def TAG_VERSION
pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo 'Building...'
                       //sh '''pio account logout || true 
                       //PLATFORMIO_AUTH_TOKEN=${MX_PLATFORMIO_AUTH_TOKEN} pio remote run -r ''' 
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Tagging stable') {
            when {
                branch 'stable' 
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
                   withCredentials([string(credentialsId: 'github_token', variable: 'TOKEN')]) {
                        sh '''git remote set-url origin https://${TOKEN}@github.com/lruizv/arduino_ultrasonic_radar.git'''
                        sh '''git push origin --tags'''
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
                //sh '''pio account logout || true 
                //PLATFORMIO_AUTH_TOKEN=${MX_PLATFORMIO_AUTH_TOKEN} pio remote run --environment uno --target upload'''
            }
        }
    }
    environment {
    MX_PLATFORMIO_AUTH_TOKEN = credentials('MX_PLATFORMIO_AUTH_TOKEN')
  }
}