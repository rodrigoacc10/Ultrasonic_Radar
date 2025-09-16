def TAG_VERSION
def SELECTED_ENV_TOKEN
def SELECTED_ENV
pipeline {
    agent any
    stages {
        stage('Selecting Environment') {
            steps {
                echo 'Selecting Environment...'
                    script {
                    env.RELEASE_SCOPE = input message: 'User input required', ok: 'Select',
                            parameters: [choice(name: 'RELEASE_SCOPE', choices: 'MX\nMCH', description: 'Which environment do you want to use?')] 
                                if (env.RELEASE_SCOPE == 'MX') {
                                    echo "Using to MX..."
                                    SELECTED_ENV = "uno_lrv"
                                    SELECTED_ENV_TOKEN = MX_PLATFORMIO_AUTH_TOKEN
                                } else if (env.RELEASE_SCOPE == 'MCH') {
                                    echo "Using to MCH..."
                                    SELECTED_ENV = "uno"
                                    SELECTED_ENV_TOKEN = MX_PLATFORMIO_AUTH_TOKEN
                                } else {
                                    echo "Deploying to Other"
                                }      
                }
                echo "ENV: ${SELECTED_ENV}"
                echo "${env.RELEASE_SCOPE}"                
            }
        }
        stage('Build') {
            steps {
                
                echo 'Building...'
                       sh "pio run -e ${SELECTED_ENV} -vvv"
            }
        }
        stage('HW Test') {
            steps {
                echo 'Testing..'
                echo "ENV: ${SELECTED_ENV}"
                    sh "PLATFORMIO_AUTH_TOKEN=${SELECTED_ENV_TOKEN} pio remote test -e ${SELECTED_ENV} -vvv"
            }
        }
        stage('Logic Test') {
            steps {
                echo 'Testing..'
                echo "ENV: ${SELECTED_ENV}"
                    sh "pio test -e native -vvv"
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
                sh "PLATFORMIO_AUTH_TOKEN=${SELECTED_ENV_TOKEN} pio remote run --environment ${SELECTED_ENV} --target upload"
            }
        }
    }
    environment {
    MX_PLATFORMIO_AUTH_TOKEN = credentials('MX_PLATFORMIO_AUTH_TOKEN')
  }
}