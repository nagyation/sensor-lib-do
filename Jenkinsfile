node {
    stage('Preparation') {
        git url: 'https://github.com/conative-labs/sensor-lib-do',
        branch: 'master'
        sh 'ceedling upgrade test_suite' // prepare test_suite insiders
    }
    
    stage('Unit Test') {
        dir("test_suite") {
            sh 'ceedling'
        }
    }
}
